#ifndef CLASS_REGISTER_H_
#define CLASS_REGISTER_H_

#include <map>
#include <string>

#define CLASS_REGISTER_DEFINE_REGISTRY(register_name, base_class_name)				\
	class ObjectCreatorRegistry_##register_name {									\
	  public:																		\
	    typedef base_class_name* (*Creator)();										\
		ObjectCreatorRegistry_##register_name(){}									\
		~ObjectCreatorRegistry_##register_name(){}									\
        void AddCreator(const std::string entryName, Creator creator){				\
			m_creator_registry[entryName] = creator;								\
		}																			\
		base_class_name* CreateObject(const std::string &entryName);				\
	  private:																		\
		typedef std::map<std::string, Creator> CreatorRegistry;						\
		CreatorRegistry m_creator_registry;											\
	};																				\
	inline ObjectCreatorRegistry_##register_name&									\
		GetRegistry_##register_name(){												\
			static ObjectCreatorRegistry_##register_name registry;					\
			return registry;														\
	}																				\
	class ObjectCreatorRegister_##register_name {									\
		public:																		\
			ObjectCreatorRegister_##register_name(									\
					const std::string entryName,									\
					ObjectCreatorRegistry_##register_name::Creator creator){		\
				GetRegistry_##register_name().AddCreator(entryName,creator);		\
			}																		\
			virtual ~ObjectCreatorRegister_##register_name(){}						\
	};																				\


#define CLASS_REGISTER_IMPLEMENT_REGISTRY(register_name, base_class_name)			\
    base_class_name* ObjectCreatorRegistry_##register_name::CreateObject(			\
		const std::string &entryName){												\
		Creator creator = NULL;														\
		CreatorRegistry::const_iterator itr =										\
			m_creator_registry.find(entryName);										\
		if(itr != m_creator_registry.end()) {										\
			creator = itr->second;													\
		}																			\
		if(creator != NULL) {														\
			return (*creator)();													\
		}																			\
		else																		\
			return NULL;															\
	}																				

#define CLASS_REGISTER_OBJECT_CREATOR(												\
		register_name, base_class_name, class_name, entryName)						\
	base_class_name* ObjectCreator_##register_name_##class_name(){					\
		return new class_name;														\
	}																				\
	ObjectCreatorRegister_##register_name											\
		g_object_creator_##register_name_##class_name(entryName,ObjectCreator_##register_name_##class_name);					\

#define CLASS_REGISTER_CREATE_OBJECT(												\
		register_name,entryName)													\
	GetRegistry_##register_name().CreateObject(entryName);	

#endif
