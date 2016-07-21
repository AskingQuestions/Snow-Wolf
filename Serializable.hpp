#ifndef Serializable_Def
#define Serializable_Def
namespace Serializable {
	
};

class ISerializable {
public:
	virtual DataStructure Serialize() {
		
	}
	
	virtual DataStructure Deserialize(DataStructure ds) {
		
	}
};

#endif