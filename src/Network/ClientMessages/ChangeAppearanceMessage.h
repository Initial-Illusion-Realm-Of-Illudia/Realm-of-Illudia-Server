#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

/**
 * @brief Client tells it wants to change the appearance of a character
 * 
 * Sent when making a new character or when changing
 * the appearance of an existing character.
 */
struct ChangeAppearanceMessage : BaseClientMessage
{
    ClientMessageType MessageType = ClientMessageType::ChangeAppearance;
    int8_t PeopleKind; /** < See Game/Appearance/PeopleKind.h */
    int8_t BodyLength;
    int8_t BodyWidth;
    int8_t ArmLength;
    int8_t ArmWidth;
    int8_t LegLength;
    int8_t LegWidth;
    int8_t ChestSize;
    int8_t ChestSeparation;
    int8_t ChestWidth;
    int8_t TorsoLength;
    int8_t MidWidth;
    int8_t HeadShape; /** < Hardcoded values */
    int8_t HeadWidth;
    int8_t HairStyle;
    int8_t FacialHair;  /** < Hardcoded values */
    int8_t Stubble;  /** < Hardcoded values */
    int8_t MouthBottomSize;
    int8_t CheekSnarl;
    int8_t CheekBone;
    int8_t EyesType;  /** < Hardcoded values */
    int8_t EyeHeight;
    int8_t EyeSeperation;
    int8_t EyeRotation;
    int8_t EyeSize;
    int8_t EyeLid;
    int8_t BrowInnerHeight;
    int8_t BrowInnerScale;
    int8_t BrowOuterHeight;
    int8_t BrowOuterScale;
    int8_t EarHeight;
    int8_t EarSeperation;
    int8_t EarRotation;
    int8_t EarSize;
    int8_t FaceComplexion;  /** < Hardcoded values */
    int8_t FaceDetails;  /** < Hardcoded values */
    int8_t FaceExtraDetails;  /** < Hardcoded values */
    int8_t FaceWrinkles;  /** < Hardcoded values */
    int8_t NoseBridgeHeight;
    int8_t NoseBridgeSize;
    int8_t NosePosition;
    int8_t NoseTipHeight;
    int8_t NoseTipSize;
    int8_t NosetrilHeight;
    int8_t NosetrilSize;
    int8_t JawHeight;
    int8_t JawSize;
    int8_t ChinHeight;
    int8_t ChinWidth;
    int8_t ChinDepth;
    int8_t MouthType;  /** < Hardcoded values */
    int8_t MouthPosition;
    int8_t MouthSize;
    int8_t MouthTopSize;
    int8_t MouthCornerHeight;
    int8_t MouthBottomScale;
    int32_t SkinColor;
    int32_t HairColor;
    int32_t EyeColor;
    int32_t LipsColor;
};