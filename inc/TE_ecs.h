#ifndef TEECS_H_
#define TEECS_H_

#include<cstdint>
#include<bitset>
#include<queue>
#include<array>
#include<unordered_map>
#include<assert.h>
#include<memory>
#include<set>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 100;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager{
private:
    std::queue<Entity> mAvailableEntities{};
    std::array<Signature, MAX_ENTITIES> mSignatures{};
    std::uint32_t mLivingEntityCount{};
public:
    EntityManager();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void SetSignature(Entity entity, Signature signature);
    Signature GetSignature(Entity entity);
};

class IComponentArray{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray: public IComponentArray{
private:
    std::array<T,MAX_ENTITIES> mComponentArray;
    std::unordered_map<Entity, size_t> mEntityToIndexMap;
    std::unordered_map<size_t, Entity> mIndexToEntityMap;
    size_t mSize;
public:
    void InsertData(Entity entity, T component);
    void RemoveData(Entity entity);
    T& GetData(Entity entity);
    void EntityDestroyed(Entity entity) override;

};

class ComponentManager{
private:
    std::unordered_map<const char*, ComponentType> mComponentTypes{};
    std::unordered_map<const char*,std::shared_ptr<IComponentArray>> mComponentArrays{};
    ComponentType mNextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();
public:
    template<typename T>
    void RegisterComponent();
    template<typename T>
    ComponentType GetComponentType();
    template<typename T>
    void AddComponent(Entity entity, T component);
    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    T& GetComponent(Entity entity);
    void EntityDestroyed(Entity entity);
};

class System{
public:
    std::set<Entity> mEntities;
};

class SystemManager{
private:
    std::unordered_map<const char*, Signature> mSignatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem();
    template<typename T>
    void SetSignature(Signature signature);
    void EntityDestroyed(Entity entity);
    void EntitySignatureChanged(Entity entity, Signature entitySignature);
};

class Coordinator{
private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;
public:
    void Init();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    template<typename T>
    void RegisterComponent();
    template<typename T>
    void AddComponent(Entity entity, T component);
    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    T& GetComponent(Entity entity);
    template<typename T>
    ComponentType GetComponentType();
    template<typename T>
    std::shared_ptr<T> RegisterSystem();
    template<typename T>
    void SetSystemSignature(Signature signature);
};
#endif