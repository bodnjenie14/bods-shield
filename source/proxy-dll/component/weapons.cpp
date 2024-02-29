#include <std_include.hpp>

#include "weapons.hpp"
#include "gsc_funcs.hpp"
#include "hashes.hpp"

#include "definitions/game.hpp"
#include "definitions/variables.hpp"
#include "definitions/xassets.hpp"
#include "definitions/game.hpp"
#include "definitions/dynamic_data.hpp"

#include "loader/component_loader.hpp"
#include <utilities/hook.hpp>
#include <utilities/io.hpp>

namespace weapons
{
	namespace
	{
		dynamic_data::field weapon_def_fields[]
		{
			{ gsc_funcs::canon_hash_pattern("weaponheadobjectiveheight"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def::weaponheadobjectiveheight), 1, offsetof(xassets::weapon_def, weaponheadobjectiveheight) },
            { gsc_funcs::canon_hash_pattern("baseWeapon"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::baseWeapon), 1, offsetof(xassets::weapon_def, baseWeapon) },
            { gsc_funcs::canon_hash_pattern("displayname"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::displayname), 1, offsetof(xassets::weapon_def, displayname) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk30), 1, offsetof(xassets::weapon_def, unk30) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk40), 1, offsetof(xassets::weapon_def, unk40) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk50), 1, offsetof(xassets::weapon_def, unk50) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk60), 1, offsetof(xassets::weapon_def, unk60) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk70), 1, offsetof(xassets::weapon_def, unk70) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk80), 1, offsetof(xassets::weapon_def, unk80) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound90), 1, offsetof(xassets::weapon_def, sound90) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sounda0), 1, offsetof(xassets::weapon_def, sounda0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::soundb0), 1, offsetof(xassets::weapon_def, soundb0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::soundc0), 1, offsetof(xassets::weapon_def, soundc0) },
            { gsc_funcs::canon_hash_pattern("firesounddistant"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::firesounddistant), 1, offsetof(xassets::weapon_def, firesounddistant) },
            { gsc_funcs::canon_hash_pattern("firesound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::firesound), 1, offsetof(xassets::weapon_def, firesound) },
            { gsc_funcs::canon_hash_pattern("firesoundplayer"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::firesoundplayer), 1, offsetof(xassets::weapon_def, firesoundplayer) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound100), 1, offsetof(xassets::weapon_def, sound100) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound110), 1, offsetof(xassets::weapon_def, sound110) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound120), 1, offsetof(xassets::weapon_def, sound120) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound130), 1, offsetof(xassets::weapon_def, sound130) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound140), 1, offsetof(xassets::weapon_def, sound140) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound150), 1, offsetof(xassets::weapon_def, sound150) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound160), 1, offsetof(xassets::weapon_def, sound160) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound170), 1, offsetof(xassets::weapon_def, sound170) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound180), 1, offsetof(xassets::weapon_def, sound180) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound190), 1, offsetof(xassets::weapon_def, sound190) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1a0), 1, offsetof(xassets::weapon_def, sound1a0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1b0), 1, offsetof(xassets::weapon_def, sound1b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1c0), 1, offsetof(xassets::weapon_def, sound1c0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1d0), 1, offsetof(xassets::weapon_def, sound1d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1e0), 1, offsetof(xassets::weapon_def, sound1e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound1f0), 1, offsetof(xassets::weapon_def, sound1f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound200), 1, offsetof(xassets::weapon_def, sound200) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound210), 1, offsetof(xassets::weapon_def, sound210) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound220), 1, offsetof(xassets::weapon_def, sound220) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound230), 1, offsetof(xassets::weapon_def, sound230) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound240), 1, offsetof(xassets::weapon_def, sound240) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound250), 1, offsetof(xassets::weapon_def, sound250) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound260), 1, offsetof(xassets::weapon_def, sound260) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound270), 1, offsetof(xassets::weapon_def, sound270) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound280), 1, offsetof(xassets::weapon_def, sound280) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound290), 1, offsetof(xassets::weapon_def, sound290) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2a0), 1, offsetof(xassets::weapon_def, sound2a0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2b0), 1, offsetof(xassets::weapon_def, sound2b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2c0), 1, offsetof(xassets::weapon_def, sound2c0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2d0), 1, offsetof(xassets::weapon_def, sound2d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2e0), 1, offsetof(xassets::weapon_def, sound2e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound2f0), 1, offsetof(xassets::weapon_def, sound2f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound300), 1, offsetof(xassets::weapon_def, sound300) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound310), 1, offsetof(xassets::weapon_def, sound310) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound320), 1, offsetof(xassets::weapon_def, sound320) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound330), 1, offsetof(xassets::weapon_def, sound330) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound340), 1, offsetof(xassets::weapon_def, sound340) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound350), 1, offsetof(xassets::weapon_def, sound350) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound360), 1, offsetof(xassets::weapon_def, sound360) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound370), 1, offsetof(xassets::weapon_def, sound370) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound380), 1, offsetof(xassets::weapon_def, sound380) },
            { gsc_funcs::canon_hash_pattern("gadgetreadysound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::gadgetreadysound), 1, offsetof(xassets::weapon_def, gadgetreadysound) },
            { gsc_funcs::canon_hash_pattern("var_1f7ccc3b"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::var_1f7ccc3b), 1, offsetof(xassets::weapon_def, var_1f7ccc3b) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound3b0), 1, offsetof(xassets::weapon_def, sound3b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound3c0), 1, offsetof(xassets::weapon_def, sound3c0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound3d0), 1, offsetof(xassets::weapon_def, sound3d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound3e0), 1, offsetof(xassets::weapon_def, sound3e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound3f0), 1, offsetof(xassets::weapon_def, sound3f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound400), 1, offsetof(xassets::weapon_def, sound400) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound410), 1, offsetof(xassets::weapon_def, sound410) },
            { gsc_funcs::canon_hash_pattern("gadgetreadysoundplayer"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::gadgetreadysoundplayer), 1, offsetof(xassets::weapon_def, gadgetreadysoundplayer) },
            { gsc_funcs::canon_hash_pattern("var_fb22040b"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::var_fb22040b), 1, offsetof(xassets::weapon_def, var_fb22040b) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound440), 1, offsetof(xassets::weapon_def, sound440) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound450), 1, offsetof(xassets::weapon_def, sound450) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound460), 1, offsetof(xassets::weapon_def, sound460) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound470), 1, offsetof(xassets::weapon_def, sound470) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound480), 1, offsetof(xassets::weapon_def, sound480) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound490), 1, offsetof(xassets::weapon_def, sound490) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4a0), 1, offsetof(xassets::weapon_def, sound4a0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4b0), 1, offsetof(xassets::weapon_def, sound4b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4c0), 1, offsetof(xassets::weapon_def, sound4c0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4d0), 1, offsetof(xassets::weapon_def, sound4d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4e0), 1, offsetof(xassets::weapon_def, sound4e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound4f0), 1, offsetof(xassets::weapon_def, sound4f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound500), 1, offsetof(xassets::weapon_def, sound500) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound510), 1, offsetof(xassets::weapon_def, sound510) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound520), 1, offsetof(xassets::weapon_def, sound520) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound530), 1, offsetof(xassets::weapon_def, sound530) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound540), 1, offsetof(xassets::weapon_def, sound540) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound550), 1, offsetof(xassets::weapon_def, sound550) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound560), 1, offsetof(xassets::weapon_def, sound560) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound570), 1, offsetof(xassets::weapon_def, sound570) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound580), 1, offsetof(xassets::weapon_def, sound580) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound590), 1, offsetof(xassets::weapon_def, sound590) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5a0), 1, offsetof(xassets::weapon_def, sound5a0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5b0), 1, offsetof(xassets::weapon_def, sound5b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5c0), 1, offsetof(xassets::weapon_def, sound5c0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5d0), 1, offsetof(xassets::weapon_def, sound5d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5e0), 1, offsetof(xassets::weapon_def, sound5e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound5f0), 1, offsetof(xassets::weapon_def, sound5f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound600), 1, offsetof(xassets::weapon_def, sound600) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound610), 1, offsetof(xassets::weapon_def, sound610) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound620), 1, offsetof(xassets::weapon_def, sound620) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound630), 1, offsetof(xassets::weapon_def, sound630) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound640), 1, offsetof(xassets::weapon_def, sound640) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound650), 1, offsetof(xassets::weapon_def, sound650) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound660), 1, offsetof(xassets::weapon_def, sound660) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound670), 1, offsetof(xassets::weapon_def, sound670) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound680), 1, offsetof(xassets::weapon_def, sound680) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound690), 1, offsetof(xassets::weapon_def, sound690) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound6a0), 1, offsetof(xassets::weapon_def, sound6a0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound6b0), 1, offsetof(xassets::weapon_def, sound6b0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound6c0), 1, offsetof(xassets::weapon_def, sound6c0) },
            { gsc_funcs::canon_hash_pattern("lockonseekersearchsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::lockonseekersearchsound), 1, offsetof(xassets::weapon_def, lockonseekersearchsound) },
            { gsc_funcs::canon_hash_pattern("lockonseekerlockedsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::lockonseekerlockedsound), 1, offsetof(xassets::weapon_def, lockonseekerlockedsound) },
            { gsc_funcs::canon_hash_pattern("lockontargetlockedsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::lockontargetlockedsound), 1, offsetof(xassets::weapon_def, lockontargetlockedsound) },
            { gsc_funcs::canon_hash_pattern("lockontargetfiredonsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::lockontargetfiredonsound), 1, offsetof(xassets::weapon_def, lockontargetfiredonsound) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound710), 1, offsetof(xassets::weapon_def, sound710) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound720), 1, offsetof(xassets::weapon_def, sound720) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound730), 1, offsetof(xassets::weapon_def, sound730) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound740), 1, offsetof(xassets::weapon_def, sound740) },
            { gsc_funcs::canon_hash_pattern("var_8a03df2b"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::var_8a03df2b), 1, offsetof(xassets::weapon_def, var_8a03df2b) },
            { gsc_funcs::canon_hash_pattern("var_2f3ca476"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::var_2f3ca476), 1, offsetof(xassets::weapon_def, var_2f3ca476) },
            { gsc_funcs::canon_hash_pattern("var_5c29f743"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::var_5c29f743), 1, offsetof(xassets::weapon_def, var_5c29f743) },
            { gsc_funcs::canon_hash_pattern("projexplosionsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::projexplosionsound), 1, offsetof(xassets::weapon_def, projexplosionsound) },
            { gsc_funcs::canon_hash_pattern("projexplosionsoundplayer"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::projexplosionsoundplayer), 1, offsetof(xassets::weapon_def, projexplosionsoundplayer) },
            { gsc_funcs::canon_hash_pattern("projsmokestartsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::projsmokestartsound), 1, offsetof(xassets::weapon_def, projsmokestartsound) },
            { gsc_funcs::canon_hash_pattern("projsmokeloopsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::projsmokeloopsound), 1, offsetof(xassets::weapon_def, projsmokeloopsound) },
            { gsc_funcs::canon_hash_pattern("projsmokeendsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::projsmokeendsound), 1, offsetof(xassets::weapon_def, projsmokeendsound) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound7d0), 1, offsetof(xassets::weapon_def, sound7d0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound7e0), 1, offsetof(xassets::weapon_def, sound7e0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound7f0), 1, offsetof(xassets::weapon_def, sound7f0) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound800), 1, offsetof(xassets::weapon_def, sound800) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound810), 1, offsetof(xassets::weapon_def, sound810) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound820), 1, offsetof(xassets::weapon_def, sound820) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound830), 1, offsetof(xassets::weapon_def, sound830) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound840), 1, offsetof(xassets::weapon_def, sound840) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound850), 1, offsetof(xassets::weapon_def, sound850) },
            { 0, dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::sound860), 1, offsetof(xassets::weapon_def, sound860) },
            { gsc_funcs::canon_hash_pattern("hitsound"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::hitsound), 1, offsetof(xassets::weapon_def, hitsound) },
            { gsc_funcs::canon_hash_pattern("unk880"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def::unk880), 1, offsetof(xassets::weapon_def, unk880) },
		};

		dynamic_data::field weapon_properties_fields[]
		{
            { gsc_funcs::canon_hash_pattern("var_77b46a8c"), dynamic_data::FT_XHASH, sizeof(xassets::weapon_def_properties::var_77b46a8c), 1, offsetof(xassets::weapon_def_properties, var_77b46a8c) },
            { gsc_funcs::canon_hash_pattern("explosionouterdamage"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::explosionouterdamage), 1, offsetof(xassets::weapon_def_properties, explosionouterdamage) },
            { gsc_funcs::canon_hash_pattern("gadget_shockfield_radius"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_shockfield_radius), 1, offsetof(xassets::weapon_def_properties, gadget_shockfield_radius) },
            { gsc_funcs::canon_hash_pattern("gadget_shockfield_damage"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_shockfield_damage), 1, offsetof(xassets::weapon_def_properties, gadget_shockfield_damage) },
            { gsc_funcs::canon_hash_pattern("gadget_flickerondamage"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_flickerondamage), 1, offsetof(xassets::weapon_def_properties, gadget_flickerondamage) },
            { gsc_funcs::canon_hash_pattern("gadget_flickeronpowerloss"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_flickeronpowerloss), 1, offsetof(xassets::weapon_def_properties, gadget_flickeronpowerloss) },
            { gsc_funcs::canon_hash_pattern("var_e4109b63"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_e4109b63), 1, offsetof(xassets::weapon_def_properties, var_e4109b63) },
            { gsc_funcs::canon_hash_pattern("gadget_max_hitpoints"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_max_hitpoints), 1, offsetof(xassets::weapon_def_properties, gadget_max_hitpoints) },
            { gsc_funcs::canon_hash_pattern("var_c4d4d2a9"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_c4d4d2a9), 1, offsetof(xassets::weapon_def_properties, var_c4d4d2a9) },
            { gsc_funcs::canon_hash_pattern("gadget_powerofflossondamage"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_powerofflossondamage), 1, offsetof(xassets::weapon_def_properties, gadget_powerofflossondamage) },
            { gsc_funcs::canon_hash_pattern("gadget_powergainonretrieve"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_powergainonretrieve), 1, offsetof(xassets::weapon_def_properties, gadget_powergainonretrieve) },
            { gsc_funcs::canon_hash_pattern("gadget_powergainscorefactor"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_powergainscorefactor), 1, offsetof(xassets::weapon_def_properties, gadget_powergainscorefactor) },
            { gsc_funcs::canon_hash_pattern("var_c15c6b39"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_c15c6b39), 1, offsetof(xassets::weapon_def_properties, var_c15c6b39) },
            { gsc_funcs::canon_hash_pattern("var_6a864cad"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_6a864cad), 1, offsetof(xassets::weapon_def_properties, var_6a864cad) },
            { gsc_funcs::canon_hash_pattern("gadget_powermoveloss"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_powermoveloss), 1, offsetof(xassets::weapon_def_properties, gadget_powermoveloss) },
            { gsc_funcs::canon_hash_pattern("gadget_powermovespeed"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_powermovespeed), 1, offsetof(xassets::weapon_def_properties, gadget_powermovespeed) },
            { gsc_funcs::canon_hash_pattern("gadget_poweronlossondamage"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_poweronlossondamage), 1, offsetof(xassets::weapon_def_properties, gadget_poweronlossondamage) },
            { gsc_funcs::canon_hash_pattern("var_58543a1c"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_58543a1c), 1, offsetof(xassets::weapon_def_properties, var_58543a1c) },
            { gsc_funcs::canon_hash_pattern("var_68a0f062"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_68a0f062), 1, offsetof(xassets::weapon_def_properties, var_68a0f062) },
            { gsc_funcs::canon_hash_pattern("var_abb570e0"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_abb570e0), 1, offsetof(xassets::weapon_def_properties, var_abb570e0) },
            { gsc_funcs::canon_hash_pattern("var_829de2ac"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_829de2ac), 1, offsetof(xassets::weapon_def_properties, var_829de2ac) },
            { gsc_funcs::canon_hash_pattern("var_e4d4fa7e"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_e4d4fa7e), 1, offsetof(xassets::weapon_def_properties, var_e4d4fa7e) },
            { gsc_funcs::canon_hash_pattern("gadget_powerreplenishfactor"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_powerreplenishfactor), 1, offsetof(xassets::weapon_def_properties, gadget_powerreplenishfactor) },
            { gsc_funcs::canon_hash_pattern("gadget_power_round_end_active_penalty"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_power_round_end_active_penalty), 1, offsetof(xassets::weapon_def_properties, gadget_power_round_end_active_penalty) },
            { gsc_funcs::canon_hash_pattern("gadget_powersprintloss"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_powersprintloss), 1, offsetof(xassets::weapon_def_properties, gadget_powersprintloss) },
            { gsc_funcs::canon_hash_pattern("var_d911d477"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_d911d477), 1, offsetof(xassets::weapon_def_properties, var_d911d477) },
            { gsc_funcs::canon_hash_pattern("gadget_power_usage_rate"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::gadget_power_usage_rate), 1, offsetof(xassets::weapon_def_properties, gadget_power_usage_rate) },
            { gsc_funcs::canon_hash_pattern("var_e1811962"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_e1811962), 1, offsetof(xassets::weapon_def_properties, var_e1811962) },
            { gsc_funcs::canon_hash_pattern("var_66103577"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_66103577), 1, offsetof(xassets::weapon_def_properties, var_66103577) },
            { gsc_funcs::canon_hash_pattern("var_f9eec1ec"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_f9eec1ec), 1, offsetof(xassets::weapon_def_properties, var_f9eec1ec) },
            { gsc_funcs::canon_hash_pattern("var_6821283d"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_6821283d), 1, offsetof(xassets::weapon_def_properties, var_6821283d) },
            { gsc_funcs::canon_hash_pattern("var_81683931"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_81683931), 1, offsetof(xassets::weapon_def_properties, var_81683931) },
            { gsc_funcs::canon_hash_pattern("var_1e89f40"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_1e89f40), 1, offsetof(xassets::weapon_def_properties, var_1e89f40) },
            { gsc_funcs::canon_hash_pattern("gadget_pulse_duration"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_pulse_duration), 1, offsetof(xassets::weapon_def_properties, gadget_pulse_duration) },
            { gsc_funcs::canon_hash_pattern("var_4d88a1ff"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_4d88a1ff), 1, offsetof(xassets::weapon_def_properties, var_4d88a1ff) },
            { gsc_funcs::canon_hash_pattern("var_9d776ba6"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_9d776ba6), 1, offsetof(xassets::weapon_def_properties, var_9d776ba6) },
            { gsc_funcs::canon_hash_pattern("var_b9951041"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_b9951041), 1, offsetof(xassets::weapon_def_properties, var_b9951041) },
            { gsc_funcs::canon_hash_pattern("var_8e0b0827"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_8e0b0827), 1, offsetof(xassets::weapon_def_properties, var_8e0b0827) },
            { gsc_funcs::canon_hash_pattern("var_a2d7b97c"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_a2d7b97c), 1, offsetof(xassets::weapon_def_properties, var_a2d7b97c) },
            { gsc_funcs::canon_hash_pattern("var_5be370e9"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_5be370e9), 1, offsetof(xassets::weapon_def_properties, var_5be370e9) },
            { gsc_funcs::canon_hash_pattern("var_42a3cafc"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_42a3cafc), 1, offsetof(xassets::weapon_def_properties, var_42a3cafc) },
            { gsc_funcs::canon_hash_pattern("gadget_pulse_max_range"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::gadget_pulse_max_range), 1, offsetof(xassets::weapon_def_properties, gadget_pulse_max_range) },
            { gsc_funcs::canon_hash_pattern("var_44c79c09"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_44c79c09), 1, offsetof(xassets::weapon_def_properties, var_44c79c09) },
            { gsc_funcs::canon_hash_pattern("var_2cb95b88"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_2cb95b88), 1, offsetof(xassets::weapon_def_properties, var_2cb95b88) },
            { gsc_funcs::canon_hash_pattern("gadget_turnoff_onempjammed"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_turnoff_onempjammed), 1, offsetof(xassets::weapon_def_properties, gadget_turnoff_onempjammed) },
            { gsc_funcs::canon_hash_pattern("gadget_heroversion_2_0"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_heroversion_2_0), 1, offsetof(xassets::weapon_def_properties, gadget_heroversion_2_0) },
            { gsc_funcs::canon_hash_pattern("var_256488f1"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_256488f1), 1, offsetof(xassets::weapon_def_properties, var_256488f1) },
            { gsc_funcs::canon_hash_pattern("gadget_powergainscoreignoreself"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_powergainscoreignoreself), 1, offsetof(xassets::weapon_def_properties, gadget_powergainscoreignoreself) },
            { gsc_funcs::canon_hash_pattern("var_f23e9d19"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_f23e9d19), 1, offsetof(xassets::weapon_def_properties, var_f23e9d19) },
            { gsc_funcs::canon_hash_pattern("gadget_powergainscoreignorewhenactive"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_powergainscoreignorewhenactive), 1, offsetof(xassets::weapon_def_properties, gadget_powergainscoreignorewhenactive) },
            { gsc_funcs::canon_hash_pattern("var_ddaa57f2"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_ddaa57f2), 1, offsetof(xassets::weapon_def_properties, var_ddaa57f2) },
            { gsc_funcs::canon_hash_pattern("gadget_power_reset_on_class_change"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_power_reset_on_class_change), 1, offsetof(xassets::weapon_def_properties, gadget_power_reset_on_class_change) },
            { gsc_funcs::canon_hash_pattern("gadget_power_reset_on_spawn"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_power_reset_on_spawn), 1, offsetof(xassets::weapon_def_properties, gadget_power_reset_on_spawn) },
            { gsc_funcs::canon_hash_pattern("gadget_power_reset_on_team_change"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_power_reset_on_team_change), 1, offsetof(xassets::weapon_def_properties, gadget_power_reset_on_team_change) },
            { gsc_funcs::canon_hash_pattern("gadget_power_reset_on_round_switch"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_power_reset_on_round_switch), 1, offsetof(xassets::weapon_def_properties, gadget_power_reset_on_round_switch) },
            { gsc_funcs::canon_hash_pattern("gadget_power_consume_on_ammo_use"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::gadget_power_consume_on_ammo_use), 1, offsetof(xassets::weapon_def_properties, gadget_power_consume_on_ammo_use) },
            { gsc_funcs::canon_hash_pattern("var_5801b768"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_5801b768), 1, offsetof(xassets::weapon_def_properties, var_5801b768) },
            { gsc_funcs::canon_hash_pattern("var_bec5136b"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_bec5136b), 1, offsetof(xassets::weapon_def_properties, var_bec5136b) },
            { gsc_funcs::canon_hash_pattern("var_28bb357c"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_28bb357c), 1, offsetof(xassets::weapon_def_properties, var_28bb357c) },
            { gsc_funcs::canon_hash_pattern("var_f10d73e1"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_f10d73e1), 1, offsetof(xassets::weapon_def_properties, var_f10d73e1) },
            { gsc_funcs::canon_hash_pattern("var_7b5016a7"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_7b5016a7), 1, offsetof(xassets::weapon_def_properties, var_7b5016a7) },
            { gsc_funcs::canon_hash_pattern("var_ce34bb7e"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_ce34bb7e), 1, offsetof(xassets::weapon_def_properties, var_ce34bb7e) },
            { gsc_funcs::canon_hash_pattern("var_27c94b15"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_27c94b15), 1, offsetof(xassets::weapon_def_properties, var_27c94b15) },
            { gsc_funcs::canon_hash_pattern("var_16e90b80"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_16e90b80), 1, offsetof(xassets::weapon_def_properties, var_16e90b80) },
            { gsc_funcs::canon_hash_pattern("var_6cb9946f"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_6cb9946f), 1, offsetof(xassets::weapon_def_properties, var_6cb9946f) },
            { gsc_funcs::canon_hash_pattern("var_40ffe7d2"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_40ffe7d2), 1, offsetof(xassets::weapon_def_properties, var_40ffe7d2) },
            { gsc_funcs::canon_hash_pattern("aimeleerange"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::aimeleerange), 1, offsetof(xassets::weapon_def_properties, aimeleerange) },
            { gsc_funcs::canon_hash_pattern("var_6844746b"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_6844746b), 1, offsetof(xassets::weapon_def_properties, var_6844746b) },
            { gsc_funcs::canon_hash_pattern("var_e2b40cd5"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_e2b40cd5), 1, offsetof(xassets::weapon_def_properties, var_e2b40cd5) },
            { gsc_funcs::canon_hash_pattern("damagetoownerscalar"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::damagetoownerscalar), 1, offsetof(xassets::weapon_def_properties, damagetoownerscalar) },
            { gsc_funcs::canon_hash_pattern("var_c94f007c"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_c94f007c), 1, offsetof(xassets::weapon_def_properties, var_c94f007c) },
            { gsc_funcs::canon_hash_pattern("var_3a00e7eb"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_3a00e7eb), 1, offsetof(xassets::weapon_def_properties, var_3a00e7eb) },
            { gsc_funcs::canon_hash_pattern("var_2cf65b96"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_2cf65b96), 1, offsetof(xassets::weapon_def_properties, var_2cf65b96) },
            { gsc_funcs::canon_hash_pattern("adsspread"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::adsspread), 1, offsetof(xassets::weapon_def_properties, adsspread) },
            { gsc_funcs::canon_hash_pattern("fightdist"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::fightdist), 1, offsetof(xassets::weapon_def_properties, fightdist) },
            { gsc_funcs::canon_hash_pattern("var_1f13c7f1"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_1f13c7f1), 1, offsetof(xassets::weapon_def_properties, var_1f13c7f1) },
            { gsc_funcs::canon_hash_pattern("var_5af80bb6"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_5af80bb6), 1, offsetof(xassets::weapon_def_properties, var_5af80bb6) },
            { gsc_funcs::canon_hash_pattern("var_36c76157"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_36c76157), 1, offsetof(xassets::weapon_def_properties, var_36c76157) },
            { gsc_funcs::canon_hash_pattern("var_19f920eb"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_19f920eb), 1, offsetof(xassets::weapon_def_properties, var_19f920eb) },
            { gsc_funcs::canon_hash_pattern("maxdist"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::maxdist), 1, offsetof(xassets::weapon_def_properties, maxdist) },
            { gsc_funcs::canon_hash_pattern("maxgibdistance"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::maxgibdistance), 1, offsetof(xassets::weapon_def_properties, maxgibdistance) },
            { gsc_funcs::canon_hash_pattern("meleelungerange"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::meleelungerange), 1, offsetof(xassets::weapon_def_properties, meleelungerange) },
            { gsc_funcs::canon_hash_pattern("var_9aa1ef19"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_9aa1ef19), 1, offsetof(xassets::weapon_def_properties, var_9aa1ef19) },
            { gsc_funcs::canon_hash_pattern("var_cd539cb2"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_cd539cb2), 1, offsetof(xassets::weapon_def_properties, var_cd539cb2) },
            { gsc_funcs::canon_hash_pattern("var_cb3d0f65"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_cb3d0f65), 1, offsetof(xassets::weapon_def_properties, var_cb3d0f65) },
            { gsc_funcs::canon_hash_pattern("var_7872b3a"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_7872b3a), 1, offsetof(xassets::weapon_def_properties, var_7872b3a) },
            { gsc_funcs::canon_hash_pattern("var_367c47fc"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_367c47fc), 1, offsetof(xassets::weapon_def_properties, var_367c47fc) },
            { gsc_funcs::canon_hash_pattern("var_ccebc40"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_ccebc40), 1, offsetof(xassets::weapon_def_properties, var_ccebc40) },
            { gsc_funcs::canon_hash_pattern("var_deb0b2fe"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_deb0b2fe), 1, offsetof(xassets::weapon_def_properties, var_deb0b2fe) },
            { gsc_funcs::canon_hash_pattern("lifetime"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::lifetime), 1, offsetof(xassets::weapon_def_properties, lifetime) },
            { gsc_funcs::canon_hash_pattern("sprintboostduration"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::sprintboostduration), 1, offsetof(xassets::weapon_def_properties, sprintboostduration) },
            { gsc_funcs::canon_hash_pattern("sprintboostradius"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::sprintboostradius), 1, offsetof(xassets::weapon_def_properties, sprintboostradius) },
            { gsc_funcs::canon_hash_pattern("lockonlossanglehorizontal"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::lockonlossanglehorizontal), 1, offsetof(xassets::weapon_def_properties, lockonlossanglehorizontal) },
            { gsc_funcs::canon_hash_pattern("lockonlossanglevertical"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::lockonlossanglevertical), 1, offsetof(xassets::weapon_def_properties, lockonlossanglevertical) },
            { gsc_funcs::canon_hash_pattern("lockonanglehorizontal"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::lockonanglehorizontal), 1, offsetof(xassets::weapon_def_properties, lockonanglehorizontal) },
            { gsc_funcs::canon_hash_pattern("lockonanglevertical"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::lockonanglevertical), 1, offsetof(xassets::weapon_def_properties, lockonanglevertical) },
            { gsc_funcs::canon_hash_pattern("vehicleprojectiledamagescalar"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::vehicleprojectiledamagescalar), 1, offsetof(xassets::weapon_def_properties, vehicleprojectiledamagescalar) },
            { gsc_funcs::canon_hash_pattern("vehicleprojectilesplashdamagescalar"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::vehicleprojectilesplashdamagescalar), 1, offsetof(xassets::weapon_def_properties, vehicleprojectilesplashdamagescalar) },
            { gsc_funcs::canon_hash_pattern("var_416021d8"), dynamic_data::FT_FLOAT, sizeof(xassets::weapon_def_properties::var_416021d8), 1, offsetof(xassets::weapon_def_properties, var_416021d8) },
            { gsc_funcs::canon_hash_pattern("aiFuseTime"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::aiFuseTime), 1, offsetof(xassets::weapon_def_properties, aiFuseTime) },
            { gsc_funcs::canon_hash_pattern("burndamage"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::burndamage), 1, offsetof(xassets::weapon_def_properties, burndamage) },
            { gsc_funcs::canon_hash_pattern("burndamageinterval"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::burndamageinterval), 1, offsetof(xassets::weapon_def_properties, burndamageinterval) },
            { gsc_funcs::canon_hash_pattern("burnduration"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::burnduration), 1, offsetof(xassets::weapon_def_properties, burnduration) },
            { gsc_funcs::canon_hash_pattern("burstcount"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::burstcount), 1, offsetof(xassets::weapon_def_properties, burstcount) },
            { gsc_funcs::canon_hash_pattern("var_98333ae"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_98333ae), 1, offsetof(xassets::weapon_def_properties, var_98333ae) },
            { gsc_funcs::canon_hash_pattern("var_1c0e3cb7"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_1c0e3cb7), 1, offsetof(xassets::weapon_def_properties, var_1c0e3cb7) },
            { gsc_funcs::canon_hash_pattern("var_4941de5"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_4941de5), 1, offsetof(xassets::weapon_def_properties, var_4941de5) },
            { gsc_funcs::canon_hash_pattern("var_f7e67f28"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_f7e67f28), 1, offsetof(xassets::weapon_def_properties, var_f7e67f28) },
            { gsc_funcs::canon_hash_pattern("var_227c90e1"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_227c90e1), 1, offsetof(xassets::weapon_def_properties, var_227c90e1) },
            { gsc_funcs::canon_hash_pattern("var_ab300840"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_ab300840), 1, offsetof(xassets::weapon_def_properties, var_ab300840) },
            { gsc_funcs::canon_hash_pattern("var_849af6b4"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_849af6b4), 1, offsetof(xassets::weapon_def_properties, var_849af6b4) },
            { gsc_funcs::canon_hash_pattern("var_c4aae0fa"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_c4aae0fa), 1, offsetof(xassets::weapon_def_properties, var_c4aae0fa) },
            { gsc_funcs::canon_hash_pattern("var_5ac2e7a4"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_5ac2e7a4), 1, offsetof(xassets::weapon_def_properties, var_5ac2e7a4) },
            { gsc_funcs::canon_hash_pattern("var_76127e14"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_76127e14), 1, offsetof(xassets::weapon_def_properties, var_76127e14) },
            { gsc_funcs::canon_hash_pattern("var_df381b5d"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_df381b5d), 1, offsetof(xassets::weapon_def_properties, var_df381b5d) },
            { gsc_funcs::canon_hash_pattern("var_a8bd8bb2"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_a8bd8bb2), 1, offsetof(xassets::weapon_def_properties, var_a8bd8bb2) },
            { gsc_funcs::canon_hash_pattern("var_8134b209"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_8134b209), 1, offsetof(xassets::weapon_def_properties, var_8134b209) },
            { gsc_funcs::canon_hash_pattern("heal"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::heal), 1, offsetof(xassets::weapon_def_properties, heal) },
            { gsc_funcs::canon_hash_pattern("var_4465ef1e"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_4465ef1e), 1, offsetof(xassets::weapon_def_properties, var_4465ef1e) },
            { gsc_funcs::canon_hash_pattern("ammoindex"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::ammoindex), 1, offsetof(xassets::weapon_def_properties, ammoindex) },
            { gsc_funcs::canon_hash_pattern("iClipSize"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::iClipSize), 1, offsetof(xassets::weapon_def_properties, iClipSize) },
            { gsc_funcs::canon_hash_pattern("var_ec2cbce2"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_ec2cbce2), 1, offsetof(xassets::weapon_def_properties, var_ec2cbce2) },
            { gsc_funcs::canon_hash_pattern("var_df0f9ce9"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_df0f9ce9), 1, offsetof(xassets::weapon_def_properties, var_df0f9ce9) },
            { gsc_funcs::canon_hash_pattern("var_1123a989"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_1123a989), 1, offsetof(xassets::weapon_def_properties, var_1123a989) },
            { gsc_funcs::canon_hash_pattern("iMaxAmmo"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::iMaxAmmo), 1, offsetof(xassets::weapon_def_properties, iMaxAmmo) },
            { gsc_funcs::canon_hash_pattern("meleedamage"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleedamage), 1, offsetof(xassets::weapon_def_properties, meleedamage) },
            { gsc_funcs::canon_hash_pattern("meleetime"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleetime), 1, offsetof(xassets::weapon_def_properties, meleetime) },
            { gsc_funcs::canon_hash_pattern("iStartAmmo"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::iStartAmmo), 1, offsetof(xassets::weapon_def_properties, iStartAmmo) },
            { gsc_funcs::canon_hash_pattern("fuellife"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::fuellife), 1, offsetof(xassets::weapon_def_properties, fuellife) },
            { gsc_funcs::canon_hash_pattern("lockonlossradius"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::lockonlossradius), 1, offsetof(xassets::weapon_def_properties, lockonlossradius) },
            { gsc_funcs::canon_hash_pattern("lockonminrange"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::lockonminrange), 1, offsetof(xassets::weapon_def_properties, lockonminrange) },
            { gsc_funcs::canon_hash_pattern("lockonradius"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::lockonradius), 1, offsetof(xassets::weapon_def_properties, lockonradius) },
            { gsc_funcs::canon_hash_pattern("lockonscreenradius"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::lockonscreenradius), 1, offsetof(xassets::weapon_def_properties, lockonscreenradius) },
            { gsc_funcs::canon_hash_pattern("maxheal"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::maxheal), 1, offsetof(xassets::weapon_def_properties, maxheal) },
            { gsc_funcs::canon_hash_pattern("maxinstancesallowed"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::maxinstancesallowed), 1, offsetof(xassets::weapon_def_properties, maxinstancesallowed) },
            { gsc_funcs::canon_hash_pattern("meleechargetime"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleechargetime), 1, offsetof(xassets::weapon_def_properties, meleechargetime) },
            { gsc_funcs::canon_hash_pattern("meleepowertime"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleepowertime), 1, offsetof(xassets::weapon_def_properties, meleepowertime) },
            { gsc_funcs::canon_hash_pattern("meleepowertimeleft"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleepowertimeleft), 1, offsetof(xassets::weapon_def_properties, meleepowertimeleft) },
            { gsc_funcs::canon_hash_pattern("var_cddb5cd0"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_cddb5cd0), 1, offsetof(xassets::weapon_def_properties, var_cddb5cd0) },
            { gsc_funcs::canon_hash_pattern("var_e5db3b95"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_e5db3b95), 1, offsetof(xassets::weapon_def_properties, var_e5db3b95) },
            { gsc_funcs::canon_hash_pattern("var_61d29b2f"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_61d29b2f), 1, offsetof(xassets::weapon_def_properties, var_61d29b2f) },
            { gsc_funcs::canon_hash_pattern("multidetonation"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::multidetonation), 1, offsetof(xassets::weapon_def_properties, multidetonation) },
            { gsc_funcs::canon_hash_pattern("var_c264efc6"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_c264efc6), 1, offsetof(xassets::weapon_def_properties, var_c264efc6) },
            { gsc_funcs::canon_hash_pattern("var_95d8fabf"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_95d8fabf), 1, offsetof(xassets::weapon_def_properties, var_95d8fabf) },
            { gsc_funcs::canon_hash_pattern("playerdamage"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::playerdamage), 1, offsetof(xassets::weapon_def_properties, playerdamage) },
            { gsc_funcs::canon_hash_pattern("var_ac36c1db"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_ac36c1db), 1, offsetof(xassets::weapon_def_properties, var_ac36c1db) },
            { gsc_funcs::canon_hash_pattern("var_60563796"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_60563796), 1, offsetof(xassets::weapon_def_properties, var_60563796) },
            { gsc_funcs::canon_hash_pattern("var_7a93ed37"), dynamic_data::FT_INT, sizeof(xassets::weapon_def_properties::var_7a93ed37), 1, offsetof(xassets::weapon_def_properties, var_7a93ed37) },
            { gsc_funcs::canon_hash_pattern("ammoCountClipRelative"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ammoCountClipRelative), 1, offsetof(xassets::weapon_def_properties, ammoCountClipRelative) },
            { gsc_funcs::canon_hash_pattern("var_8032088a"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_8032088a), 1, offsetof(xassets::weapon_def_properties, var_8032088a) },
            { gsc_funcs::canon_hash_pattern("ammoregen"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ammoregen), 1, offsetof(xassets::weapon_def_properties, ammoregen) },
            { gsc_funcs::canon_hash_pattern("var_f6dea63a"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_f6dea63a), 1, offsetof(xassets::weapon_def_properties, var_f6dea63a) },
            { gsc_funcs::canon_hash_pattern("altoffhand"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::altoffhand), 1, offsetof(xassets::weapon_def_properties, altoffhand) },
            { gsc_funcs::canon_hash_pattern("bAltWeaponDisableSwitching"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::bAltWeaponDisableSwitching), 1, offsetof(xassets::weapon_def_properties, bAltWeaponDisableSwitching) },
            { gsc_funcs::canon_hash_pattern("anyplayercanretrieve"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::anyplayercanretrieve), 1, offsetof(xassets::weapon_def_properties, anyplayercanretrieve) },
            { gsc_funcs::canon_hash_pattern("isboltaction"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isboltaction), 1, offsetof(xassets::weapon_def_properties, isboltaction) },
            { gsc_funcs::canon_hash_pattern("bulletimpactexplode"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::bulletimpactexplode), 1, offsetof(xassets::weapon_def_properties, bulletimpactexplode) },
            { gsc_funcs::canon_hash_pattern("canuseunderwater"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::canuseunderwater), 1, offsetof(xassets::weapon_def_properties, canuseunderwater) },
            { gsc_funcs::canon_hash_pattern("iscliponly"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::iscliponly), 1, offsetof(xassets::weapon_def_properties, iscliponly) },
            { gsc_funcs::canon_hash_pattern("var_337fc1cf"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_337fc1cf), 1, offsetof(xassets::weapon_def_properties, var_337fc1cf) },
            { gsc_funcs::canon_hash_pattern("craftitem"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::craftitem), 1, offsetof(xassets::weapon_def_properties, craftitem) },
            { gsc_funcs::canon_hash_pattern("var_9fffdcee"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_9fffdcee), 1, offsetof(xassets::weapon_def_properties, var_9fffdcee) },
            { gsc_funcs::canon_hash_pattern("decoy"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::decoy), 1, offsetof(xassets::weapon_def_properties, decoy) },
            { gsc_funcs::canon_hash_pattern("destroyablebytrophysystem"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::destroyablebytrophysystem), 1, offsetof(xassets::weapon_def_properties, destroyablebytrophysystem) },
            { gsc_funcs::canon_hash_pattern("bDieOnRespawn"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::bDieOnRespawn), 1, offsetof(xassets::weapon_def_properties, bDieOnRespawn) },
            { gsc_funcs::canon_hash_pattern("disabledeploy"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::disabledeploy), 1, offsetof(xassets::weapon_def_properties, disabledeploy) },
            { gsc_funcs::canon_hash_pattern("disallowatmatchstart"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::disallowatmatchstart), 1, offsetof(xassets::weapon_def_properties, disallowatmatchstart) },
            { gsc_funcs::canon_hash_pattern("dodamagefeedback"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::dodamagefeedback), 1, offsetof(xassets::weapon_def_properties, dodamagefeedback) },
            { gsc_funcs::canon_hash_pattern("doempdestroyfx"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::doempdestroyfx), 1, offsetof(xassets::weapon_def_properties, doempdestroyfx) },
            { gsc_funcs::canon_hash_pattern("doesfiredamage"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::doesfiredamage), 1, offsetof(xassets::weapon_def_properties, doesfiredamage) },
            { gsc_funcs::canon_hash_pattern("dohackedstats"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::dohackedstats), 1, offsetof(xassets::weapon_def_properties, dohackedstats) },
            { gsc_funcs::canon_hash_pattern("dostun"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::dostun), 1, offsetof(xassets::weapon_def_properties, dostun) },
            { gsc_funcs::canon_hash_pattern("isdualwield"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isdualwield), 1, offsetof(xassets::weapon_def_properties, isdualwield) },
            { gsc_funcs::canon_hash_pattern("var_251796e3"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_251796e3), 1, offsetof(xassets::weapon_def_properties, var_251796e3) },
            { gsc_funcs::canon_hash_pattern("ignoresflakjacket"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ignoresflakjacket), 1, offsetof(xassets::weapon_def_properties, ignoresflakjacket) },
            { gsc_funcs::canon_hash_pattern("ignoreslightarmor"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ignoreslightarmor), 1, offsetof(xassets::weapon_def_properties, ignoreslightarmor) },
            { gsc_funcs::canon_hash_pattern("ignorespowerarmor"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ignorespowerarmor), 1, offsetof(xassets::weapon_def_properties, ignorespowerarmor) },
            { gsc_funcs::canon_hash_pattern("ignoreteamkills"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ignoreteamkills), 1, offsetof(xassets::weapon_def_properties, ignoreteamkills) },
            { gsc_funcs::canon_hash_pattern("isaikillstreakdamage"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isaikillstreakdamage), 1, offsetof(xassets::weapon_def_properties, isaikillstreakdamage) },
            { gsc_funcs::canon_hash_pattern("isballisticknife"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isballisticknife), 1, offsetof(xassets::weapon_def_properties, isballisticknife) },
            { gsc_funcs::canon_hash_pattern("iscarriedkillstreak"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::iscarriedkillstreak), 1, offsetof(xassets::weapon_def_properties, iscarriedkillstreak) },
            { gsc_funcs::canon_hash_pattern("isemp"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isemp), 1, offsetof(xassets::weapon_def_properties, isemp) },
            { gsc_funcs::canon_hash_pattern("isflash"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isflash), 1, offsetof(xassets::weapon_def_properties, isflash) },
            { gsc_funcs::canon_hash_pattern("isflourishweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isflourishweapon), 1, offsetof(xassets::weapon_def_properties, isflourishweapon) },
            { gsc_funcs::canon_hash_pattern("isgameplayweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isgameplayweapon), 1, offsetof(xassets::weapon_def_properties, isgameplayweapon) },
            { gsc_funcs::canon_hash_pattern("ishacktoolweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::ishacktoolweapon), 1, offsetof(xassets::weapon_def_properties, ishacktoolweapon) },
            { gsc_funcs::canon_hash_pattern("bIsHybridWeapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::bIsHybridWeapon), 1, offsetof(xassets::weapon_def_properties, bIsHybridWeapon) },
            { gsc_funcs::canon_hash_pattern("isperkbottle"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isperkbottle), 1, offsetof(xassets::weapon_def_properties, isperkbottle) },
            { gsc_funcs::canon_hash_pattern("isscavengable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isscavengable), 1, offsetof(xassets::weapon_def_properties, isscavengable) },
            { gsc_funcs::canon_hash_pattern("issniperweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::issniperweapon), 1, offsetof(xassets::weapon_def_properties, issniperweapon) },
            { gsc_funcs::canon_hash_pattern("isstun"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isstun), 1, offsetof(xassets::weapon_def_properties, isstun) },
            { gsc_funcs::canon_hash_pattern("issupplydropweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::issupplydropweapon), 1, offsetof(xassets::weapon_def_properties, issupplydropweapon) },
            { gsc_funcs::canon_hash_pattern("var_130391b9"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_130391b9), 1, offsetof(xassets::weapon_def_properties, var_130391b9) },
            { gsc_funcs::canon_hash_pattern("var_6f12adba"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_6f12adba), 1, offsetof(xassets::weapon_def_properties, var_6f12adba) },
            { gsc_funcs::canon_hash_pattern("blocksprone"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::blocksprone), 1, offsetof(xassets::weapon_def_properties, blocksprone) },
            { gsc_funcs::canon_hash_pattern("meleeignoreslightarmor"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::meleeignoreslightarmor), 1, offsetof(xassets::weapon_def_properties, meleeignoreslightarmor) },
            { gsc_funcs::canon_hash_pattern("nohitmarker"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::nohitmarker), 1, offsetof(xassets::weapon_def_properties, nohitmarker) },
            { gsc_funcs::canon_hash_pattern("nonstowedweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::nonstowedweapon), 1, offsetof(xassets::weapon_def_properties, nonstowedweapon) },
            { gsc_funcs::canon_hash_pattern("notkillstreak"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::notkillstreak), 1, offsetof(xassets::weapon_def_properties, notkillstreak) },
            { gsc_funcs::canon_hash_pattern("setusedstat"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::setusedstat), 1, offsetof(xassets::weapon_def_properties, setusedstat) },
            { gsc_funcs::canon_hash_pattern("shownenemyequip"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::shownenemyequip), 1, offsetof(xassets::weapon_def_properties, shownenemyequip) },
            { gsc_funcs::canon_hash_pattern("shownenemyexplo"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::shownenemyexplo), 1, offsetof(xassets::weapon_def_properties, shownenemyexplo) },
            { gsc_funcs::canon_hash_pattern("shownretrievable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::shownretrievable), 1, offsetof(xassets::weapon_def_properties, shownretrievable) },
            { gsc_funcs::canon_hash_pattern("skipbattlechatterkill"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::skipbattlechatterkill), 1, offsetof(xassets::weapon_def_properties, skipbattlechatterkill) },
            { gsc_funcs::canon_hash_pattern("skipbattlechatterreload"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::skipbattlechatterreload), 1, offsetof(xassets::weapon_def_properties, skipbattlechatterreload) },
            { gsc_funcs::canon_hash_pattern("skiplowammovox"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::skiplowammovox), 1, offsetof(xassets::weapon_def_properties, skiplowammovox) },
            { gsc_funcs::canon_hash_pattern("specialpain"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::specialpain), 1, offsetof(xassets::weapon_def_properties, specialpain) },
            { gsc_funcs::canon_hash_pattern("isthrowback"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isthrowback), 1, offsetof(xassets::weapon_def_properties, isthrowback) },
            { gsc_funcs::canon_hash_pattern("var_9111ccc0"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_9111ccc0), 1, offsetof(xassets::weapon_def_properties, var_9111ccc0) },
            { gsc_funcs::canon_hash_pattern("damagealwayskillsplayer"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::damagealwayskillsplayer), 1, offsetof(xassets::weapon_def_properties, damagealwayskillsplayer) },
            { gsc_funcs::canon_hash_pattern("deployable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::deployable), 1, offsetof(xassets::weapon_def_properties, deployable) },
            { gsc_funcs::canon_hash_pattern("var_e0d42861"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_e0d42861), 1, offsetof(xassets::weapon_def_properties, var_e0d42861) },
            { gsc_funcs::canon_hash_pattern("var_3344c07e"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_3344c07e), 1, offsetof(xassets::weapon_def_properties, var_3344c07e) },
            { gsc_funcs::canon_hash_pattern("var_70b09d5b"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_70b09d5b), 1, offsetof(xassets::weapon_def_properties, var_70b09d5b) },
            { gsc_funcs::canon_hash_pattern("destroysequipment"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::destroysequipment), 1, offsetof(xassets::weapon_def_properties, destroysequipment) },
            { gsc_funcs::canon_hash_pattern("var_8025ffca"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_8025ffca), 1, offsetof(xassets::weapon_def_properties, var_8025ffca) },
            { gsc_funcs::canon_hash_pattern("var_f076a292"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_f076a292), 1, offsetof(xassets::weapon_def_properties, var_f076a292) },
            { gsc_funcs::canon_hash_pattern("doannihilate"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::doannihilate), 1, offsetof(xassets::weapon_def_properties, doannihilate) },
            { gsc_funcs::canon_hash_pattern("var_6262fd11"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_6262fd11), 1, offsetof(xassets::weapon_def_properties, var_6262fd11) },
            { gsc_funcs::canon_hash_pattern("doblowback"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::doblowback), 1, offsetof(xassets::weapon_def_properties, doblowback) },
            { gsc_funcs::canon_hash_pattern("dogibbing"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::dogibbing), 1, offsetof(xassets::weapon_def_properties, dogibbing) },
            { gsc_funcs::canon_hash_pattern("dogibbingonmelee"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::dogibbingonmelee), 1, offsetof(xassets::weapon_def_properties, dogibbingonmelee) },
            { gsc_funcs::canon_hash_pattern("donotdamageowner"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::donotdamageowner), 1, offsetof(xassets::weapon_def_properties, donotdamageowner) },
            { gsc_funcs::canon_hash_pattern("forcedamagehitlocation"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::forcedamagehitlocation), 1, offsetof(xassets::weapon_def_properties, forcedamagehitlocation) },
            { gsc_funcs::canon_hash_pattern("var_33d50507"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_33d50507), 1, offsetof(xassets::weapon_def_properties, var_33d50507) },
            { gsc_funcs::canon_hash_pattern("grappleweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::grappleweapon), 1, offsetof(xassets::weapon_def_properties, grappleweapon) },
            { gsc_funcs::canon_hash_pattern("var_fab9617b"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_fab9617b), 1, offsetof(xassets::weapon_def_properties, var_fab9617b) },
            { gsc_funcs::canon_hash_pattern("var_ca947940"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_ca947940), 1, offsetof(xassets::weapon_def_properties, var_ca947940) },
            { gsc_funcs::canon_hash_pattern("isnotdroppable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isnotdroppable), 1, offsetof(xassets::weapon_def_properties, isnotdroppable) },
            { gsc_funcs::canon_hash_pattern("issignatureweapon"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::issignatureweapon), 1, offsetof(xassets::weapon_def_properties, issignatureweapon) },
            { gsc_funcs::canon_hash_pattern("istacticalinsertion"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::istacticalinsertion), 1, offsetof(xassets::weapon_def_properties, istacticalinsertion) },
            { gsc_funcs::canon_hash_pattern("var_76ce72e8"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_76ce72e8), 1, offsetof(xassets::weapon_def_properties, var_76ce72e8) },
            { gsc_funcs::canon_hash_pattern("var_ff0b00ba"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_ff0b00ba), 1, offsetof(xassets::weapon_def_properties, var_ff0b00ba) },
            { gsc_funcs::canon_hash_pattern("isvaluable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::isvaluable), 1, offsetof(xassets::weapon_def_properties, isvaluable) },
            { gsc_funcs::canon_hash_pattern("var_29d24e37"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_29d24e37), 1, offsetof(xassets::weapon_def_properties, var_29d24e37) },
            { gsc_funcs::canon_hash_pattern("mountable"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::mountable), 1, offsetof(xassets::weapon_def_properties, mountable) },
            { gsc_funcs::canon_hash_pattern("var_ba335ef"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_ba335ef), 1, offsetof(xassets::weapon_def_properties, var_ba335ef) },
            { gsc_funcs::canon_hash_pattern("noadslockoncheck"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::noadslockoncheck), 1, offsetof(xassets::weapon_def_properties, noadslockoncheck) },
            { gsc_funcs::canon_hash_pattern("var_d69ee9ed"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_d69ee9ed), 1, offsetof(xassets::weapon_def_properties, var_d69ee9ed) },
            { gsc_funcs::canon_hash_pattern("requirelockontofire"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::requirelockontofire), 1, offsetof(xassets::weapon_def_properties, requirelockontofire) },
            { gsc_funcs::canon_hash_pattern("var_8072cf0b"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_8072cf0b), 1, offsetof(xassets::weapon_def_properties, var_8072cf0b) },
            { gsc_funcs::canon_hash_pattern("istimeddetonation"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::istimeddetonation), 1, offsetof(xassets::weapon_def_properties, istimeddetonation) },
            { gsc_funcs::canon_hash_pattern("unlimitedAmmo"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::unlimitedAmmo), 1, offsetof(xassets::weapon_def_properties, unlimitedAmmo) },
            { gsc_funcs::canon_hash_pattern("var_18608bfe"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_18608bfe), 1, offsetof(xassets::weapon_def_properties, var_18608bfe) },
            { gsc_funcs::canon_hash_pattern("var_775d2aad"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_775d2aad), 1, offsetof(xassets::weapon_def_properties, var_775d2aad) },
            { gsc_funcs::canon_hash_pattern("var_b8a85edd"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_b8a85edd), 1, offsetof(xassets::weapon_def_properties, var_b8a85edd) },
            { gsc_funcs::canon_hash_pattern("var_dbbd4cec"), dynamic_data::FT_UINT, sizeof(xassets::weapon_def_properties::var_dbbd4cec), 1, offsetof(xassets::weapon_def_properties, var_dbbd4cec) },

        // TODO: enums
        // gadgetType_e gadget_type; // 0x3c0
        // guidedMissileType_t guidedMissileType; // 0x410
        // OffhandClass offhandClass;
        // OffhandSlot offhandSlot;
        // weapClass_t weapClass; // 0x580
        // weapInventoryType_t inventoryType;
        // lockOnType_t lockontype;
        // projExplosionType_t projExplosionType;
        // weapType_t weapType; // 0x5c0
		};
		struct mod_weapon
		{
			xassets::weapon_def def{};
			xassets::weapon_def_properties props{};
			byte* def_mask[sizeof(xassets::weapon_def)]{};
			byte* props_mask[sizeof(xassets::weapon_def_properties)]{};
		};
		std::unordered_map<uint64_t, std::shared_ptr<mod_weapon>> defs_delta{};
	}

	void* get_or_patch_weapon(void* weapon_def)
	{
        if (!weapon_def)
        {
            return weapon_def;
        }
		// patch already existing weapon def
		xassets::weapon_def* def = (xassets::weapon_def*)weapon_def;
		uint64_t name = def->name.hash;

		auto it = defs_delta.find(name & 0x7FFFFFFFFFFFFFFFuLL);

		if (it == defs_delta.end())
		{
			return weapon_def;
		}

		const mod_weapon& weap = *it->second;

		// patch weapon
		utilities::hook::copy(def, &weap.def, weap.def_mask, sizeof(weap.def));
        utilities::hook::copy(def->properties, &weap.props, weap.props_mask, sizeof(weap.props));

		return def;
	}

	void* get_weapon_asset(uint64_t name)
	{
		return nullptr; // todo: not implemented
	}

	void clear_weapon_defs() {
		defs_delta.clear();
	}

	bool load_weapon_def(rapidjson::Value& member, const char* mod_name, const std::filesystem::path& mod_path) {
		auto name_mb = member.FindMember("name");
		auto path_mb = member.FindMember("path");
        auto format_mb = member.FindMember("format");

		if (
			name_mb == member.MemberEnd() || path_mb == member.MemberEnd() || format_mb == member.MemberEnd()
			|| !name_mb->value.IsString() || !path_mb->value.IsString() || !format_mb->value.IsString()
			)
		{
			logger::write(logger::LOG_TYPE_WARN, std::format("mod {} is containing a bad weapon def, missing/bad name, format or path", mod_name));
			return false;
		}

		const char* format_st = format_mb->value.GetString();

		bool delta{};
		if (!_strcmpi(format_st, "delta"))
		{
			delta = true;
		}
		else if (!_strcmpi(format_st, "full"))
		{
			logger::write(logger::LOG_TYPE_WARN, std::format("mod {} is containing a full weapon, it is not implemented yet.", mod_name));
			return false;
		}
		else
		{
			logger::write(logger::LOG_TYPE_WARN, std::format("mod {} is containing weapon with an unknown format '{}'.", mod_name, format_st));
			return false;
		}

		auto def = std::make_shared<mod_weapon>();

		std::filesystem::path path_cfg = path_mb->value.GetString();
		auto weapon_file_path = path_cfg.is_absolute() ? path_cfg : (mod_path / path_cfg);


        std::string filename = weapon_file_path.string();
        std::string weapon_data{};
        if (!utilities::io::read_file(filename, &weapon_data))
        {
            logger::write(logger::LOG_TYPE_ERROR, std::format("can't read mod weapon file '{}'", filename));
            return false;
        }

        rapidjson::Document wnfo{};

        wnfo.Parse(weapon_data);

        if (wnfo.HasParseError()) {
            logger::write(logger::LOG_TYPE_ERROR, std::format("can't parse weapon json data '{}'", filename));
            return false;
        }

		uint64_t hash_name = fnv1a::generate_hash_pattern(name_mb->value.GetString());
        def->def.name.hash = hash_name;
		// load def

        auto weapon_def = wnfo.FindMember("def");
        auto weapon_props = wnfo.FindMember("properties");

        try
        {
            if (weapon_def != wnfo.MemberEnd() && weapon_def->value.IsObject())
            {
                logger::write(logger::LOG_TYPE_DEBUG, "loading weapon defs");
                dynamic_data::load_dd(weapon_def->value, &def->def, def->def_mask, weapon_def_fields, ARRAYSIZE(weapon_def_fields));
            }

            if (weapon_props != wnfo.MemberEnd() && weapon_props->value.IsObject())
            {
                logger::write(logger::LOG_TYPE_DEBUG, "loading weapon properties");
                dynamic_data::load_dd(weapon_props->value, &def->props, def->props_mask, weapon_properties_fields, ARRAYSIZE(weapon_properties_fields));
            }
        }
        catch (std::runtime_error& err)
        {
            logger::write(logger::LOG_TYPE_WARN, std::format("mod {} is containing weapon with a bad definition: {}", mod_name, err.what()));
            return false;
        }

        assert(def->def.name.hash == hash_name && "DD error, redefined name");

		if (delta) {
			defs_delta[hash_name & 0x7FFFFFFFFFFFFFFFuLL] = def;
		}
		else
		{
			assert(0 && "Not implemented");
		}

		return true;
	}
}