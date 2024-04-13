#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "definitions/game.hpp"
#include "definitions/variables.hpp"
#include "command.hpp"

#include <utilities/hook.hpp>
#include <utilities/json_config.hpp>

namespace unlockall
{
	namespace
	{
		struct unlock_all_s
		{
            bool all = false;
            bool loot = false;
            bool items = false;
            bool attachments = false;
            bool emblems = false;
            bool challenges = false;
            bool classes = false;
        };

        class UnlockController
        {
        private:
            std::unordered_map<std::string, bool unlock_all_s::*> mapping = {
                {"all", &unlock_all_s::all},
                {"loot", &unlock_all_s::loot},
                {"items", &unlock_all_s::items},
                {"attachments", &unlock_all_s::attachments},
                {"emblems", &unlock_all_s::emblems},
                {"challenges", &unlock_all_s::challenges},
                {"classes", &unlock_all_s::classes}};
            unlock_all_s unlock;

        public:
            void changeValue(const std::string& name, bool value)
            {
                auto it = mapping.find(name);
                if (it != mapping.end())
                {
                    unlock.*(it->second) = value;
                }
            }

            bool getValue(const std::string& name)
            {
                auto it = mapping.find(name);
                if (it != mapping.end())
                {
                    return unlock.*(it->second);
                }
                return false;
            }
        };

		UnlockController unlock;

        // unlock_all_s unlock;

		utilities::hook::detour loot_getitemquantity_hook;
		utilities::hook::detour bg_unlockablesisitemattachmentlocked_hook;
		utilities::hook::detour bg_unlockablesisattachmentslotlocked_hook;
		utilities::hook::detour bg_unlockablesemblemorbackinglockedbychallenge_hook;
		utilities::hook::detour bg_unlockablesitemoptionlocked_hook;
		utilities::hook::detour bg_unlockedgetchallengeunlockedforindex_hook;
		utilities::hook::detour bg_emblemisentitlementbackgroundgranted_hook;
		utilities::hook::detour bg_unlockablesgetcustomclasscount_hook;
		utilities::hook::detour bg_unlockablesisitemlocked_hook;

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

		inline bool is_zm_loot(int item_id)
		{
			auto it = std::find(
				std::begin(zm_loot_table), std::end(zm_loot_table), item_id);
			if (it != std::end(zm_loot_table)) {
				return true;
			}
			return false;
		}

		int liveinventory_getitemquantity(const game::ControllerIndex_t controllerIndex, const int item_id)
		{
			if (unlock.getValue("all") || unlock.getValue("items"))
            {
				int result = is_zm_loot(item_id) ? 999 : 1;
				return result;
            }
			return loot_getitemquantity_hook.invoke<int>(controllerIndex, item_id);
		}

		bool bg_unlockedgetchallengeunlockedforindex(game::eModes mode, const game::ControllerIndex_t controllerIndex, uint16_t index, int32_t itemIndex)
		{
            if (unlock.getValue("all") || unlock.getValue("challenges"))
            {
                return true;
            }
			bg_unlockedgetchallengeunlockedforindex_hook.invoke<bool>(mode, controllerIndex, index, itemIndex);
		}

		bool bg_unlockablesitemoptionlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int itemIndex, int32_t optionIndex)
		{
            if (unlock.getValue("all") || unlock.getValue("items"))
            {
                return false;
            }
			return bg_unlockablesitemoptionlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, optionIndex);
		}

        bool bg_unlockablesisitemattachmentlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex, int32_t attachmentNum)
        {
            if (unlock.getValue("all") || unlock.getValue("attachments"))
            {
                return false;
            }
            return bg_unlockablesisitemattachmentlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, attachmentNum);
        }

        bool bg_unlockablesisattachmentslotlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex, int32_t attachmentSlotIndex)
		{
			if (unlock.getValue("all") || unlock.getValue("attachments"))
            {
                return false;
            }
			return bg_unlockablesisattachmentslotlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex, attachmentSlotIndex);
		}

		bool bg_unlockablesemblemorbackinglockedbychallenge(game::eModes mode, const game::ControllerIndex_t controllerIndex, void* challengeLookup, bool otherPlayer)
		{
			if (unlock.getValue("all") || unlock.getValue("emblems"))
            {
                return false;
            }
			return bg_unlockablesemblemorbackinglockedbychallenge_hook.invoke<bool>(mode, controllerIndex, challengeLookup, otherPlayer);
		}

		bool bg_emblemisentitlementbackgroundgranted(const game::ControllerIndex_t controllerIndex, uint16_t backgroundId)
		{
			if (unlock.getValue("all") || unlock.getValue("emblems"))
            {
                return true;
            }
			return bg_emblemisentitlementbackgroundgranted_hook.invoke<bool>(controllerIndex, backgroundId);
		}

		bool bg_unlockablesisitemlocked(game::eModes mode, const game::ControllerIndex_t controllerIndex, int32_t itemIndex)
		{
			if (unlock.getValue("all") || unlock.getValue("items"))
            {
                return false;
            }
			return bg_unlockablesisitemlocked_hook.invoke<bool>(mode, controllerIndex, itemIndex);

		}

		int32_t bg_unlockablesgetcustomclasscount(game::eModes mode, const game::ControllerIndex_t controllerIndex)
		{
			if (unlock.getValue("all") || unlock.getValue("classes"))
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
                unlock.changeValue(arg1, TF);
            }
            else
            {
                unlock.changeValue(arg1, true);
            }
        }
	}

    class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			command::add("unlock", [&](const command::params& params){unlock_func(params);});
			unlock.changeValue("all", utilities::json_config::ReadBoolean("unlock", "all", false));
			unlock.changeValue("loot", utilities::json_config::ReadBoolean("unlock", "loot", false));
			unlock.changeValue("items", utilities::json_config::ReadBoolean("unlock", "items", false));
			unlock.changeValue("attachments", utilities::json_config::ReadBoolean("unlock", "attachments", false));
			unlock.changeValue("emblems", utilities::json_config::ReadBoolean("unlock", "emblems", false));
			unlock.changeValue("challenges", utilities::json_config::ReadBoolean("unlock", "challenges", false));
			unlock.changeValue("classes", utilities::json_config::ReadBoolean("unlock", "classes", false));
			
			loot_getitemquantity_hook.create(0x1437F6ED0_g, liveinventory_getitemquantity);
			bg_unlockablesisitemattachmentlocked_hook.create(0x1406B34D0_g, bg_unlockablesisitemattachmentlocked);
			bg_unlockablesisattachmentslotlocked_hook.create(0x1406B3290_g, bg_unlockablesisattachmentslotlocked);
			bg_unlockablesemblemorbackinglockedbychallenge_hook.create(0x1406AC010_g, bg_unlockablesemblemorbackinglockedbychallenge);
			bg_unlockablesitemoptionlocked_hook.create(0x1406B5530_g, bg_unlockablesitemoptionlocked);
			bg_unlockedgetchallengeunlockedforindex_hook.create(0x1406BB410_g, bg_unlockedgetchallengeunlockedforindex);
			bg_emblemisentitlementbackgroundgranted_hook.create(0x144184D20_g, bg_emblemisentitlementbackgroundgranted);
			bg_unlockablesgetcustomclasscount_hook.create(0x1406ae060_g, bg_unlockablesgetcustomclasscount);
			bg_unlockablesisitemlocked_hook.create(0x1406B3AA0_g, bg_unlockablesisitemlocked);
        }
    };
}

REGISTER_COMPONENT(unlockall::component)