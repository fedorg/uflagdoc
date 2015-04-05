#include <vector>
#include <map>
#include <string>		//std::string::operator<<

struct FFlagDoc
{
	static const std::map<size_t, std::vector<std::string>> ObjectFlags;
	static const size_t DescWidth;
	static const size_t IndentLength;
	static const size_t GetMaxLength();
	static inline const std::string Indent(std::string& Name, std::string& Desc);
	void FFlagDoc::operator()(size_t Flag) const;
};

const std::map<size_t, std::vector<std::string>> FFlagDoc::ObjectFlags =
{
	{ 0x00000001, { "Public", "Object is visible outside its package." } },
	{ 0x00000002, { "Standalone", "Keep object around for editing even if unreferenced." } },
	{ 0x00000004, { "Native", "Native (UClass only)." } },
	{ 0x00000008, { "Transactional", "Object is transactional." } },
	{ 0x00000010, { "ClassDefaultObject", "This object is its class's default object" } },
	{ 0x00000020, { "ArchetypeObject", "This object is a template for another object - treat like a class default object" } },
	{ 0x00000040, { "Transient", "Don't save object." } },

	// This group of flags is primarily concerned with garbage collection.
	{ 0x00000080, { "RootSet", "Object will not be garbage collected, even if unreferenced." } },
	{ 0x00000100, { "Unreachable", "Object is not reachable on the object graph." } },
	{ 0x00000200, { "TagGarbageTemp", "This is a temp user flag for various utilities that need to use the garbage collector. The garbage collector itself does not interpret it." } },

	// The group of flags tracks the stages of the lifetime of a uobject
	{ 0x00000400, { "NeedLoad", "During load, indicates object needs loading." } },
	{ 0x00000800, { "AsyncLoading", "Object is being asynchronously loaded." } },
	{ 0x00001000, { "NeedPostLoad", "Object needs to be postloaded." } },
	{ 0x00002000, { "NeedPostLoadSubobjects", "During load, indicates that the object still needs to instance subobjects and fixup serialized component references" } },
	{ 0x00004000, { "PendingKill", "Objects that are pending destruction (invalid for gameplay but valid objects)" } },
	{ 0x00008000, { "BeginDestroyed", "BeginDestroy has been called on the object." } },
	{ 0x00010000, { "FinishDestroyed", "FinishDestroy has been called on the object." } },

	// Misc. Flags
	{ 0x00020000, { "BeingRegenerated", "Flagged on UObjects that are used to create UClasses (e.g. Blueprints) while they are regenerating their UClass on load (See FLinkerLoad::CreateExport())" } },
	{ 0x00040000, { "DefaultSubObject", "Flagged on subobjects that are defaults" } },
	{ 0x00080000, { "WasLoaded", "Flagged on UObjects that were loaded" } },
	{ 0x00100000, { "TextExportTransient", "Do not export object to text form (e.g. copy/paste). Generally used for sub-objects that can be regenerated from data in their parent object." } },
	{ 0x00200000, { "LoadCompleted", "Object has been completely serialized by linkerload at least once. DO NOT USE THIS FLAG, It should be replaced with RF_WasLoaded." } },
	{ 0x00400000, { "InheritableComponentTemplate", "Archetype of the object can be in its super class" } },
	{ 0x00800000, { "Async", "Object exists only on a different thread than the game thread." } }

};
const size_t FFlagDoc::IndentLength = FFlagDoc::GetMaxLength();
const size_t FFlagDoc::DescWidth = 50;