#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "definitions/game.hpp"
#include "definitions/variables.hpp"
#include "command.hpp"

#include <utilities/hook.hpp>
#include <utilities/json_config.hpp>
#include <utilities/string.hpp>

namespace game
{
	WEAK symbol<int(const int a1)> LobbySession_GetControllingLobbySession{0x1439066F0_g};
	WEAK symbol<int(const int LobbyModule, const int LobbyType)> LobbySession_GetLobbyMode{0x143906830_g};
	WEAK symbol<int(const game::ControllerIndex_t controllerIndex, const int statsLocation)> LiveStorage_DoWeHaveStats{0x1438B79D0_g};
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex)> LiveStats_GetPrestige{0x1438A7390_g};
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex)> LiveStats_GetRank{0x1438A7430_g};
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex)> LiveStats_GetXp{0x1438A78B0_g};
	WEAK symbol<int(game::eModes mode, const game::ControllerIndex_t controllerIndex, const char* name)> LiveStats_GetIntPlayerStatByKey{0x1438A66A0_g};
	WEAK symbol<int(game::eModes mode, const int Xp)> CL_Rank_GetRankForXP{0x1422EF900_g};
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

		utilities::hook::detour livestats_getxp_hook;
		utilities::hook::detour livestats_getrank_hook;
		utilities::hook::detour livestats_getprestige_hook;

		uint32_t zm_loot_table[] =
			{
				1000001, // zm_bgb_ctrl_z
				1000002, // zm_bgb_dead_of_nuclear_winter
				1000003, // zm_bgb_in_plain_sight
				1000004, // zm_bgb_licensed_contractor
				1000005, // zm_bgb_phantom_reload
				1000006, // zm_bgb_sword_flay
				1000007, // zm_bgb_whos_keeping_score
				1000008, // zm_bgb_alchemical_antithesis
				1000009, // zm_bgb_blood_debt
				1000010, // zm_bgb_extra_credit
				1000011, // zm_bgb_immolation_liquidation
				1000012, // zm_bgb_kill_joy
				1000013, // zm_bgb_shields_up
				1000014, // zm_bgb_free_fire
				1000015, // zm_bgb_power_keg
				1000016, // zm_bgb_undead_man_walking
				1000017, // zm_bgb_wall_to_wall_clearance
				1000018, // zm_bgb_cache_back
				1000019, // zm_bgb_join_the_party
				1000020, // zm_bgb_wall_power
				1000021, // talisman_box_guarantee_box_only
				1000022, // talisman_coagulant
				1000023, // talisman_extra_claymore
				1000024, // talisman_extra_frag
				1000025, // talisman_extra_molotov
				1000026, // talisman_extra_semtex
				1000027, // talisman_impatient
				1000028, // talisman_weapon_reducepapcost
				1000029, // talisman_perk_reducecost_1
				1000030, // talisman_perk_reducecost_2
				1000031, // talisman_perk_reducecost_3
				1000032, // talisman_perk_reducecost_4
				1000033, // talisman_shield_price
				1000034, // talisman_special_xp_rate
				1000035, // talisman_start_weapon_smg
				1000036, // talisman_box_guarantee_lmg
				1000037, // talisman_extra_miniturret
				1000038, // talisman_perk_start_1
				1000039, // talisman_perk_start_2
				1000040, // talisman_perk_start_3
				1000041, // talisman_perk_start_4
				1000042, // talisman_shield_durability_rare
				1000043, // talisman_start_weapon_ar
				1000044, // talisman_perk_permanent_1
				1000045, // talisman_perk_permanent_2
				1000046, // talisman_perk_permanent_3
				1000047, // talisman_perk_permanent_4
				1000048, // talisman_shield_durability_legendary
				1000049, // talisman_special_startlv2
				1000050, // talisman_start_weapon_lmg
				1000051, // talisman_special_startlv3
				1000052, // talisman_perk_mod_single
				1000053, // zm_bgb_refresh_mint
				1000054, // zm_bgb_perk_up
				1000055, // zm_bgb_conflagration_liquidation
				1000056, // zm_bgb_bullet_boost
				1000057, // zm_bgb_talkin_bout_regeneration
				1000058, // zm_bgb_dividend_yield
				1000059, // zm_bgb_suit_up
				1000060, // talisman_permanent_heroweap_armor
				1000061, // talisman_extra_self_revive
				1000062, // zm_bgb_perkaholic
				1000063, // zm_bgb_near_death_experience
				1000064, // zm_bgb_shopping_free
				1000065, // zm_bgb_reign_drops
				1000066, // zm_bgb_phoenix_up
				1000067, // zm_bgb_head_drama
				1000068, // zm_bgb_secret_shopper
				1000069  // zm_bgb_power_vacuum
		};

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

		class GameStats
		{
		public:
			int rank;
			int xp;
			int prestige;
			int paragonRank;
		};

		struct player_gamemode_stats
		{
			GameStats mp;
			GameStats zm;
		};

		player_gamemode_stats playerstats;
		std::unordered_map<std::string, bool> override_stat;

		void setplayerstat(const command::params& params)
		{
			if (params.size() < 4) return;

			std::string arg1 = params[1];
			std::string arg2 = params[2];
			std::string arg3 = params[3];

			if (arg3 == "off")
			{
				override_stat[arg2] = false;
				return;
			}

			if (!utilities::string::is_integer(arg3)) return;
			int num = std::stoi(arg3);

			override_stat[arg2] = true;

			if (arg1 == "mp")
			{
				if (arg2 == "rank") playerstats.mp.rank = num;
				if (arg2 == "xp") playerstats.mp.xp = num;
				if (arg2 == "prestige") playerstats.mp.prestige = num;
				if (arg2 == "paragonRank") playerstats.mp.paragonRank = num;
			}

			if (arg1 == "zm")
			{
				if (arg2 == "rank") playerstats.zm.rank = num;
				if (arg2 == "xp") playerstats.zm.xp = num;
				if (arg2 == "prestige") playerstats.zm.prestige = num;
				if (arg2 == "paragonRank") playerstats.zm.paragonRank = num;
			}
		}

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
			if (override_stat["rank"] && controllerIndex == game::ControllerIndex_t::CONTROLLER_INDEX_FIRST)
			{
				if (mode == game::eModes::MODE_MULTIPLAYER) return playerstats.mp.rank;
				if (mode == game::eModes::MODE_ZOMBIES) return playerstats.zm.rank;
			}

			if (game::LiveStorage_DoWeHaveStats(controllerIndex, 0))
			{
				const auto ControllingLobbySession = game::LobbySession_GetControllingLobbySession(1);
				if (game::LobbySession_GetLobbyMode(1, ControllingLobbySession) != 4)
				{
					// if (!sub_1438AE2F0(v3))
					// {
					unsigned int Xp = game::LiveStats_GetXp(mode, controllerIndex);
					unsigned int rank = game::CL_Rank_GetRankForXP(mode, Xp);
					// logger::write(logger::LOG_TYPE_INFO, "player xp(%i) rank(%i)", Xp, rank);
					return rank;
					// return game::CL_Rank_GetRankForXP(mode, 100000); // TEMP LiveStats_GetXp returns 0 but CL_Rank_GetRankForXP works.
					// }
					// v5 = sub_1438C2B00(a2);
					// if (v5)
					// {
					//     v6 = *(v5 + 27928);
					//     if (v6)
					//         return *(v6 + 12 * v3 + 24652);
					// }
				}
			}
			return 0;
		}

		int livestats_getxp_stub(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			if (override_stat["xp"] && controllerIndex == game::ControllerIndex_t::CONTROLLER_INDEX_FIRST)
			{
				if (mode == game::eModes::MODE_MULTIPLAYER) return playerstats.mp.xp;
				if (mode == game::eModes::MODE_ZOMBIES) return playerstats.zm.xp;
			}

			{
				if (game::LiveStorage_DoWeHaveStats(controllerIndex, 0))
				{
					const auto v4 = utilities::hook::invoke<uintptr_t>(0x1438C2B00_g, controllerIndex);
					if (v4)
					{
						const auto v5 = *((int64_t*)v4 + 27928);
						if (v5)
							return *(unsigned int*)(v5 + 12 * (mode + 2054));
					}
					return 0; // test returns this
				}
				return 0;
			}
			return livestats_getxp_hook.invoke<int>(mode, controllerIndex);
		}

		int livestats_getprestige_stub(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			return livestats_getprestige_hook.invoke<int>(mode, controllerIndex);
		}

		int sub_1438C2B00_stub()
		{
		}

		bool trol_stub(int a1)
		{
			// const auto res = utilities::hook::invoke<bool>(0x1438AE2F0_g, a1); // sub_1438AE2F0 returns false
			return true;
		}

		bool live_is_user_signed_in_to_demonware_stub(const game::ControllerIndex_t controllerIndex)
		{
			return false;
		}

		int LiveStorage_GetStatsBufferWithCaller(const game::ControllerIndex_t controllerIndex, int a2, const char* a3, int a4,  game::eModes mode, const int statsLocation)
		{
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			command::add("unlock", [&](const command::params& params){ unlock_func(params); });
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

			command::add("setplayerstat", [&](const command::params& params){ setplayerstat(params); });
			livestats_getxp_hook.create(0x1438A78B0_g, livestats_getxp_stub);
			livestats_getrank_hook.create(0x1438A7430_g, livestats_getrank_stub);
			// livestats_getprestige_hook.create(0x1438A7390_g, livestats_getprestige_stub);

			// utilities::hook::call(0x1438C2B00_g, sub_1438C2B00_stub); // LiveStats read ddl?
			// utilities::hook::call(0x143803FF0_g, live_is_user_signed_in_to_demonware_stub); // BAD
			utilities::hook::call(0x1438A78E7_g, trol_stub);
			command::add("get_player_level", get_player_level);
		}
	};
}

REGISTER_COMPONENT(unlockall::component)
