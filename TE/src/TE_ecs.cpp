#include"TE_ecs.hpp"

EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		this->mAvailableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(this->mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

	Entity id = this->mAvailableEntities.front();
	this->mAvailableEntities.pop();
	++this->mLivingEntityCount;

	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	this->mSignatures[entity].reset();

	this->mAvailableEntities.push(entity);
	--this->mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	this->mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	return this->mSignatures[entity];
}
template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component)
{
	assert(this->mEntityToIndexMap.find(entity) == this->mEntityToIndexMap.end() && "Component added to same entity more than once.");

	size_t newIndex = mSize;
	this->mEntityToIndexMap[entity] = newIndex;
	this->mIndexToEntityMap[newIndex] = entity;
	this->mComponentArray[newIndex] = component;
	++this->mSize;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity)
{
	assert(this->mEntityToIndexMap.find(entity) != this->mEntityToIndexMap.end() && "Removing non-existent component.");

	size_t indexOfRemovedEntity = this->mEntityToIndexMap[entity];
	size_t indexOfLastElement = mSize - 1;
	this->mComponentArray[indexOfRemovedEntity] = this->mComponentArray[indexOfLastElement];

	Entity entityOfLastElement =this-> mIndexToEntityMap[indexOfLastElement];
	this->mEntityToIndexMap[entityOfLastElement] =this-> indexOfRemovedEntity;
	this->mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

	this->mEntityToIndexMap.erase(entity);
	this->mIndexToEntityMap.erase(indexOfLastElement);

	--this->mSize;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity)
{
	assert(this->mEntityToIndexMap.find(entity) != this->mEntityToIndexMap.end() && "Retrieving non-existent component.");

	return this->mComponentArray[this->mEntityToIndexMap[entity]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity)
{
	if (this->mEntityToIndexMap.find(entity) != this->mEntityToIndexMap.end())
	{
		RemoveData(entity);
	}
}

template<typename T>
void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();

	assert(this->mComponentTypes.find(typeName) == this->mComponentTypes.end() && "Registering component type more than once.");

	this->mComponentTypes.insert({typeName, this->mNextComponentType});

	this->mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

	++this->mNextComponentType;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(T).name();

	assert(this->mComponentTypes.find(typeName) != this->mComponentTypes.end() && "Component not registered before use.");

	return this->mComponentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : this->mComponentArrays)
	{
		auto const& component = pair.second;

		component->EntityDestroyed(entity);
	}
}

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();

	assert(this->mSystems.find(typeName) == this->mSystems.end() && "Registering system more than once.");

	auto system = std::make_shared<T>();
	this->mSystems.insert({typeName, system});
	return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	assert(this->mSystems.find(typeName) != this->mSystems.end() && "System used before registered.");

	this->mSignatures.insert({typeName, signature});
}

void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : this->mSystems)
	{
		auto const& system = pair.second;

		system->mEntities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	for (auto const& pair : this->mSystems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = this->mSignatures[type];

		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->mEntities.insert(entity);
		}
		else
		{
			system->mEntities.erase(entity);
		}
	}
}

void Coordinator::Init()
{
	this->mComponentManager = std::make_unique<ComponentManager>();
	this->mEntityManager = std::make_unique<EntityManager>();
	this->mSystemManager = std::make_unique<SystemManager>();
}


Entity Coordinator::CreateEntity()
{
	return this->mEntityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity)
{
	this->mEntityManager->DestroyEntity(entity);

	this->mComponentManager->EntityDestroyed(entity);

	this->mSystemManager->EntityDestroyed(entity);
}


template<typename T>
void Coordinator::RegisterComponent()
{
	this->mComponentManager->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity entity, T component)
{
	this->mComponentManager->AddComponent<T>(entity, component);

	auto signature = this->mEntityManager->GetSignature(entity);
	signature.set(this->mComponentManager->GetComponentType<T>(), true);
	this->mEntityManager->SetSignature(entity, signature);

	this->mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void Coordinator::RemoveComponent(Entity entity)
{
	this->mComponentManager->RemoveComponent<T>(entity);

	auto signature = this->mEntityManager->GetSignature(entity);
	signature.set(this->mComponentManager->GetComponentType<T>(), false);
	this->mEntityManager->SetSignature(entity, signature);

	this->mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& Coordinator::GetComponent(Entity entity)
{
	return this->mComponentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Coordinator::GetComponentType()
{
	return this->mComponentManager->GetComponentType<T>();
}


// System methods
template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
	return this->mSystemManager->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature signature)
{
	this->mSystemManager->SetSignature<T>(signature);
}


