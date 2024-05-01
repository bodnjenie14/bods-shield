#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "definitions/game.hpp"
#include "definitions/variables.hpp"
#include "definitions/xassets.hpp"
#include "command.hpp"

#include <utilities/hook.hpp>
#include <utilities/json_config.hpp>

namespace game
{
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex)> LiveStats_GetPrestige{ 0x1438A7390_g };
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex)> LiveStats_GetRank{ 0x1438A7430_g };
	WEAK symbol<int(const game::ControllerIndex_t controllerIndex, const int statsLocation)> LiveStorage_DoWeHaveStats{ 0x1438B79D0_g };
}

namespace unlockall
{
	namespace
	{
		std::unordered_map<std::string, bool> unlock;

		utilities::hook::detour loot_getitemquantity_hook;
		utilities::hook::detour bg_unlockablesisitemattachmentlocked_hook;
		utilities::hook::detour bg_unlockablesisattachmentslotlocked_hook;
		utilities::hook::detour bg_unlockablesemblemorbackinglockedbychallenge_hook;
		utilities::hook::detour bg_unlockablesitemoptionlocked_hook;
		utilities::hook::detour bg_unlockedgetchallengeunlockedforindex_hook;
		utilities::hook::detour bg_emblemisentitlementbackgroundgranted_hook;
		utilities::hook::detour bg_unlockablesgetcustomclasscount_hook;
		utilities::hook::detour bg_unlockablesisitemlocked_hook;

		utilities::hook::detour livestats_getrank_hook;
		utilities::hook::detour livestats_getprestige_hook;

		uint32_t zm_loot_table[] =
		{
			1000001,			// zm_bgb_ctrl_z
			1000002,			// zm_bgb_dead_of_nuclear_winter
			1000003,			// zm_bgb_in_plain_sight
			1000004,			// zm_bgb_licensed_contractor
			1000005,			// zm_bgb_phantom_reload
			1000006,			// zm_bgb_sword_flay
			1000007,			// zm_bgb_whos_keeping_score
			1000008,			// zm_bgb_alchemical_antithesis
			1000009,			// zm_bgb_blood_debt
			1000010,			// zm_bgb_extra_credit
			1000011,			// zm_bgb_immolation_liquidation
			1000012,			// zm_bgb_kill_joy
			1000013,			// zm_bgb_shields_up
			1000014,			// zm_bgb_free_fire
			1000015,			// zm_bgb_power_keg
			1000016,			// zm_bgb_undead_man_walking
			1000017,			// zm_bgb_wall_to_wall_clearance
			1000018,			// zm_bgb_cache_back
			1000019,			// zm_bgb_join_the_party
			1000020,			// zm_bgb_wall_power
			1000021,			// talisman_box_guarantee_box_only
			1000022,			// talisman_coagulant
			1000023,			// talisman_extra_claymore
			1000024,			// talisman_extra_frag
			1000025,			// talisman_extra_molotov
			1000026,			// talisman_extra_semtex
			1000027,			// talisman_impatient
			1000028,			// talisman_weapon_reducepapcost
			1000029,			// talisman_perk_reducecost_1
			1000030,			// talisman_perk_reducecost_2
			1000031,			// talisman_perk_reducecost_3
			1000032,			// talisman_perk_reducecost_4
			1000033,			// talisman_shield_price
			1000034,			// talisman_special_xp_rate
			1000035,			// talisman_start_weapon_smg
			1000036,			// talisman_box_guarantee_lmg
			1000037,			// talisman_extra_miniturret
			1000038,			// talisman_perk_start_1
			1000039,			// talisman_perk_start_2
			1000040,			// talisman_perk_start_3
			1000041,			// talisman_perk_start_4
			1000042,			// talisman_shield_durability_rare
			1000043,			// talisman_start_weapon_ar
			1000044,			// talisman_perk_permanent_1 
			1000045,			// talisman_perk_permanent_2 
			1000046,			// talisman_perk_permanent_3 
			1000047,			// talisman_perk_permanent_4 
			1000048,			// talisman_shield_durability_legendary 
			1000049,			// talisman_special_startlv2 
			1000050,			// talisman_start_weapon_lmg 
			1000051,			// talisman_special_startlv3 
			1000052,			// talisman_perk_mod_single 
			1000053,			// zm_bgb_refresh_mint
			1000054,			// zm_bgb_perk_up
			1000055,			// zm_bgb_conflagration_liquidation
			1000056,			// zm_bgb_bullet_boost
			1000057,			// zm_bgb_talkin_bout_regeneration
			1000058,			// zm_bgb_dividend_yield
			1000059,			// zm_bgb_suit_up
			1000060,			// talisman_permanent_heroweap_armor
			1000061,			// talisman_extra_self_revive
			1000062,			// zm_bgb_perkaholic
			1000063,			// zm_bgb_near_death_experience
			1000064,			// zm_bgb_shopping_free
			1000065,			// zm_bgb_reign_drops
			1000066,			// zm_bgb_phoenix_up
			1000067,			// zm_bgb_head_drama
			1000068,			// zm_bgb_secret_shopper
			1000069 			// zm_bgb_power_vacuum
		};
		/*
				bool is_item_unlocked(int32_t code)
				{
					int playerlevel = 18; // TODO. Get player level
					int readcolumn = 11;

					// read from the csv
					static game::BO4_AssetRef_t custom_csv = game::AssetRef(fnv1a::generate_hash("project-bo4/internals/ranktable_mp.csv"));

					xassets::stringtable_header* table = xassets::DB_FindXAssetHeader(xassets::ASSET_TYPE_STRINGTABLE, &custom_csv, false, -1).stringtable;

					if (!table || !table->columns_count || table->columns_count < readcolumn)
					{
						return false;
					}

					for (size_t i = 0; i < playerlevel + 1; i++)
					{
						auto* rows = &table->values[i * table->columns_count];

						if (rows[0].type != xassets::STC_TYPE_INT || rows[readcolumn].type != xassets::STC_TYPE_STRING) continue;

						if (rows[0].value.int_value <= playerlevel)
						{
							if (rows[readcolumn].value.hash_value == code) return true;
							// if (strstr(rows[readcolumn].value.string_value, code) != nullptr)
							// {
							//     return true;
							// }
						}
					}
					return false;
				}
		 */

		void get_player_level()
		{
			game::eModes mode = game::Com_SessionMode_GetMode();
			const auto controller = game::ControllerIndex_t::CONTROLLER_INDEX_FIRST;

			int prestige = game::LiveStats_GetPrestige(mode, controller);
			int rank = game::LiveStats_GetRank(mode, controller);
			logger::write(logger::LOG_TYPE_INFO, "player rank(%i) prestige(%i)", rank, prestige);

			if (game::LiveStorage_DoWeHaveStats(controller, 0))
			{
				logger::write(logger::LOG_TYPE_INFO, "LiveStorage_DoWeHaveStats True");
			}
		}

		int livestats_getrank_stub(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			return 15;
			// return livestats_getrank_hook.invoke<int>(mode, controllerIndex);
		}

		int livestats_getprestige_stub(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			return 2;
			// return livestats_getprestige_hook.invoke<int>(mode, controllerIndex);
		}

		inline bool is_zm_loot(int item_id)
		{
			auto it = std::find(
				std::begin(zm_loot_table), std::end(zm_loot_table), item_id);
			if (it != std::end(zm_loot_table))
			{
				return true;
			}
			return false;
		}

		int liveinventory_getitemquantity(const game::ControllerIndex_t controllerIndex, const int item_id)
		{
			if (unlock["all"] || unlock["zm_loot"])
			{
				int result = is_zm_loot(item_id) ? 999 : 1;
				return result;
			}
			return loot_getitemquantity_hook.invoke<int>(controllerIndex, item_id);
		}

		bool bg_unlockedgetchallengeunlockedforindex(game::eModes mode, const game::ControllerIndex_t controllerIndex, uint16_t index, int32_t itemIndex)
		{
			if (unlock["all"] || unlock["challenges"])
			{
				return true;
			}
			bg_unlockedgetchallengeunlockedforindex_hook.invoke<bool>(mode, controllerIndex, index, itemIndex);
		}

		bool bg_unlockablesitemoptionlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int itemIndex, int32_t optionIndex)
		{
			if (unlock["all"] || unlock["itemoptions"])
			{
				return false;
			}
			return bg_unlockablesitemoptionlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, optionIndex);
		}

		bool bg_unlockablesisitemattachmentlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex, int32_t attachmentNum)
		{
			if (unlock["all"] || unlock["attachments"])
			{
				return false;
			}
			return bg_unlockablesisitemattachmentlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, attachmentNum);
		}

		bool bg_unlockablesisattachmentslotlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex, int32_t attachmentSlotIndex)
		{
			if (unlock["all"] || unlock["attachmentslot"])
			{
				return false;
			}
			return bg_unlockablesisattachmentslotlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, attachmentSlotIndex);
		}

		bool bg_unlockablesemblemorbackinglockedbychallenge(game::eModes mode, const game::ControllerIndex_t controllerIndex, void* challengeLookup, bool otherPlayer)
		{
			if (unlock["all"] || unlock["emblems"])
			{
				return false;
			}
			return bg_unlockablesemblemorbackinglockedbychallenge_hook.invoke<bool>(mode, controllerIndex, challengeLookup, otherPlayer);
		}

		bool bg_emblemisentitlementbackgroundgranted(const game::ControllerIndex_t controllerIndex, uint16_t backgroundId)
		{
			if (unlock["all"] || unlock["backgrounds"])
			{
				return true;
			}
			return bg_emblemisentitlementbackgroundgranted_hook.invoke<bool>(controllerIndex, backgroundId);
		}

		bool bg_unlockablesisitemlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex)
		{
			if (unlock["all"] || unlock["items"])
			{
				return false;
				// return is_item_unlocked(itemIndex);
			}
			return bg_unlockablesisitemlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex);

		}

		int32_t bg_unlockablesgetcustomclasscount(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			if (unlock["all"] || unlock["classes"])
			{
				return 12; // max 12
			}
			return bg_unlockablesgetcustomclasscount_hook.invoke<int>(mode, controllerIndex);
		}

		void unlock_func(const command::params& params)
		{
			if (params.size() < 2) return;

			std::string arg1 = params[1];

			if (params.size() == 3)
			{
				std::string arg2 = params[2];
				bool TF = (arg2 == "true" || arg2 == "True" || arg2 == "1");
				unlock[arg1] = TF;
			}
			else
			{
				unlock[arg1] = true;
			}
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			command::add("get_player_level", get_player_level);

			command::add("unlock", [&](const command::params& params) {unlock_func(params); });
			unlock["all"] = utilities::json_config::ReadBoolean("unlock", "all", false);
			unlock["attachments"] = utilities::json_config::ReadBoolean("unlock", "attachments", false);
			unlock["attachmentslot"] = utilities::json_config::ReadBoolean("unlock", "attachmentslot", false);
			unlock["backgrounds"] = utilities::json_config::ReadBoolean("unlock", "backgrounds", false);
			unlock["challenges"] = utilities::json_config::ReadBoolean("unlock", "challenges", false);
			unlock["classes"] = utilities::json_config::ReadBoolean("unlock", "classes", false);
			unlock["emblems"] = utilities::json_config::ReadBoolean("unlock", "emblems", false);
			unlock["itemoptions"] = utilities::json_config::ReadBoolean("unlock", "itemoptions", false);
			unlock["items"] = utilities::json_config::ReadBoolean("unlock", "items", false);
			unlock["zm_loot"] = utilities::json_config::ReadBoolean("unlock", "zm_loot", false);

			loot_getitemquantity_hook.create(0x1437F6ED0_g, liveinventory_getitemquantity);
			bg_unlockablesisitemattachmentlocked_hook.create(0x1406B34D0_g, bg_unlockablesisitemattachmentlocked);
			bg_unlockablesisattachmentslotlocked_hook.create(0x1406B3290_g, bg_unlockablesisattachmentslotlocked);
			bg_unlockablesemblemorbackinglockedbychallenge_hook.create(0x1406AC010_g, bg_unlockablesemblemorbackinglockedbychallenge);
			bg_unlockablesitemoptionlocked_hook.create(0x1406B5530_g, bg_unlockablesitemoptionlocked);
			bg_unlockedgetchallengeunlockedforindex_hook.create(0x1406BB410_g, bg_unlockedgetchallengeunlockedforindex);
			bg_emblemisentitlementbackgroundgranted_hook.create(0x144184D20_g, bg_emblemisentitlementbackgroundgranted);
			bg_unlockablesgetcustomclasscount_hook.create(0x1406ae060_g, bg_unlockablesgetcustomclasscount);
			bg_unlockablesisitemlocked_hook.create(0x1406B3AA0_g, bg_unlockablesisitemlocked);

			livestats_getrank_hook.create(0x1438A7430_g, livestats_getrank_stub);
			livestats_getprestige_hook.create(0x1438A7390_g, livestats_getprestige_stub);
		}
	};
}

REGISTER_COMPONENT(unlockall::component)