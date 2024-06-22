#pragma once

namespace acts
{
	// integration header of the different structures generated by acts (https://github.com/ate47/atian-cod-tools)

	namespace debug_scripting
	{
		constexpr uint64_t MAGIC = 0x0d0a42444124;
		constexpr byte CURRENT_VERSION = 0x12;

		enum GSC_ACTS_DEBUG_FEATURES : byte
		{
			ADF_STRING = 0x10,
			ADF_DETOUR = 0x11,
			ADF_DEVBLOCK_BEGIN = 0x12,
			ADF_LAZYLINK = 0x12,
		};

		struct GSC_ACTS_DETOUR
		{
			uint64_t name_space;
			uint64_t name;
			uint64_t script;
			uint32_t location;
			uint32_t size;
		};

		struct GSC_ACTS_LAZYLINK
		{
			uint64_t name_space;
			uint64_t name;
			uint64_t script;
			uint32_t num_address;
		};

		struct GSC_ACTS_DEBUG
		{
			byte magic[sizeof(MAGIC)];
			byte version;
			uint64_t actsVersion;
			uint32_t strings_offset{};
			uint32_t strings_count{};
			uint32_t detour_offset{};
			uint32_t detour_count{};
			uint32_t devblock_offset{};
			uint32_t devblock_count{};
			uint32_t lazylink_offset{};
			uint32_t lazylink_count{};

			constexpr bool has_feature(GSC_ACTS_DEBUG_FEATURES feature) const
			{
				return version >= feature;
			}

			inline GSC_ACTS_DETOUR* get_detours(byte* start)
			{
				return reinterpret_cast<GSC_ACTS_DETOUR*>(start + detour_offset);
			}

			inline GSC_ACTS_DETOUR* get_detours_end(byte* start)
			{
				return get_detours(start) + detour_count;
			}

			inline uint32_t* get_devblocks(byte* start)
			{
				return reinterpret_cast<uint32_t*>(start + devblock_offset);
			}

			inline uint32_t* get_devblocks_end(byte* start)
			{
				return get_devblocks(start) + devblock_count;
			}

			inline uint32_t* get_strings(byte* start)
			{
				return reinterpret_cast<uint32_t*>(start + strings_offset);
			}

			inline uint32_t* get_strings_end(byte* start)
			{
				return get_strings(start) + strings_count;
			}
		};

	}


}