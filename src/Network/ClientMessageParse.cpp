#include "ClientMessageParse.h"
#include "ClientMessages/AuthenticateMessage.h"
#include "ClientMessages/ActionMoveMessage.h"
#include "ClientMessages/ChangeNameMessage.h"
#include "ClientMessages/ChangeAppearanceMessage.h"
#include "ClientMessages/SelectCharacterMessage.h"

#include <cstdint>
#include <algorithm>

ClientMessageParse::ClientMessageParse(Network* innetwork)
{
    this->network = innetwork;
    this->marshaller = new Marshaller();
}

ClientMessageParse::~ClientMessageParse()
{
    delete(this->marshaller);
}

void ClientMessageParse::ParseMessage(std::istream& msg)
{
    auto messageType = this->marshaller->ReadU8(msg);
    
    if (!messageType.has_value())
    {
        return;
    }
    switch (static_cast<ClientMessageType>(messageType.value()))
    {
        case ClientMessageType::Authenticate:
    {
        AuthenticateMessage aMsg = AuthenticateMessage();
        if (!this->marshaller->ReadCharArray(msg, aMsg.Token, 64))
        {
            return;
        }
        this->network->Dispatch(aMsg);
        break;
    }
    case ClientMessageType::SelectCharacter:
    {
        SelectCharacterMessage scMsg = SelectCharacterMessage();
        auto characterId = this->marshaller->ReadU8(msg);
        if (!characterId.has_value())
        {
            return;
        }
        scMsg.Character = characterId.value();
        this->network->Dispatch(scMsg);
        break;
    }
    case ClientMessageType::ChangeName:
    {
        ChangeNameMessage ncMsg = ChangeNameMessage();
        if (!this->marshaller->ReadCharArray(msg, ncMsg.SureName, 60))
        {
            return;
        }
        if (!this->marshaller->ReadCharArray(msg, ncMsg.FamilyName, 60))
        {
            return;
        }
        this->network->Dispatch(ncMsg);
        break;
    }
    case ClientMessageType::ChangeAppearance:
    {
        ChangeAppearanceMessage ncMsg = ChangeAppearanceMessage();
        auto peopleKind = this->marshaller->ReadU8(msg);
        if (!peopleKind.has_value())
        {
            return;
        }
        ncMsg.PeopleKind = peopleKind.value();
        if (auto bodyLength = this->marshaller->ReadU8(msg))
        {
            ncMsg.BodyLength = bodyLength.value();
        }
        else
        {
            return;
        }
        if (auto bodyWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.BodyWidth = bodyWidth.value();
        }
        else
        {
            return;
        }
        if (auto armLength = this->marshaller->ReadU8(msg))
        {
            ncMsg.ArmLength = armLength.value();
        }
        else
        {
            return;
        }
        if (auto armWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.ArmWidth = armWidth.value();
        }
        else
        {
            return;
        }
        if (auto legLength = this->marshaller->ReadU8(msg))
        {
            ncMsg.LegLength = legLength.value();
        }
        else
        {
            return;
        }
        if (auto legWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.LegWidth = legWidth.value();
        }
        else
        {
            return;
        }
        if (auto chestSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChestSize = chestSize.value();
        }
        else
        {
            return;
        }
        if (auto chestSeparation = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChestSeparation = chestSeparation.value();
        }
        else
        {
            return;
        }
        if (auto chestWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChestWidth = chestWidth.value();
        }
        else
        {
            return;
        }
        if (auto torsoLength = this->marshaller->ReadU8(msg))
        {
            ncMsg.TorsoLength = torsoLength.value();
        }
        else
        {
            return;
        }
        if (auto midWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.MidWidth = midWidth.value();
        }
        else
        {
            return;
        }
        if (auto headShape = this->marshaller->ReadU8(msg))
        {
            ncMsg.HeadShape = headShape.value();
        }
        else
        {
            return;
        }
        if (auto headWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.HeadWidth = headWidth.value();
        }
        else
        {
            return;
        }
        if (auto hairStyle = this->marshaller->ReadU8(msg))
        {
            ncMsg.HairStyle = hairStyle.value();
        }
        else
        {
            return;
        }
        if (auto facialHair = this->marshaller->ReadU8(msg))
        {
            ncMsg.FacialHair = facialHair.value();
        }
        else
        {
            return;
        }
        if (auto stubble = this->marshaller->ReadU8(msg))
        {
            ncMsg.Stubble = stubble.value();
        }
        else
        {
            return;
        }
        if (auto mouthBottomSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthBottomSize = mouthBottomSize.value();
        }
        else
        {
            return;
        }
        if (auto cheekSnarl = this->marshaller->ReadU8(msg))
        {
            ncMsg.CheekSnarl = cheekSnarl.value();
        }
        else
        {
            return;
        }
        if (auto cheekBone = this->marshaller->ReadU8(msg))
        {
            ncMsg.CheekBone = cheekBone.value();
        }
        else
        {
            return;
        }
        if (auto eyesType = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyesType = eyesType.value();
        }
        else
        {
            return;
        }
        if (auto eyeHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeHeight = eyeHeight.value();
        }
        else
        {
            return;
        }
        if (auto eyeSeperation = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeSeperation = eyeSeperation.value();
        }
        else
        {
            return;
        }
        if (auto eyeRotation = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeRotation = eyeRotation.value();
        }
        else
        {
            return;
        }
        if (auto eyeSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeSize = eyeSize.value();
        }
        else
        {
            return;
        }
        if (auto eyeLid = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeLid = eyeLid.value();
        }
        else
        {
            return;
        }
        if (auto browInnerHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.BrowInnerHeight = browInnerHeight.value();
        }
        else
        {
            return;
        }
        if (auto browInnerScale = this->marshaller->ReadU8(msg))
        {
            ncMsg.BrowInnerScale = browInnerScale.value();
        }
        else
        {
            return;
        }
        if (auto browOuterHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.BrowOuterHeight = browOuterHeight.value();
        }
        else
        {
            return;
        }
        if (auto browOuterScale = this->marshaller->ReadU8(msg))
        {
            ncMsg.BrowOuterScale = browOuterScale.value();
        }
        else
        {
            return;
        }
        if (auto earHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.EarHeight = earHeight.value();
        }
        else
        {
            return;
        }
        if (auto earSeperation = this->marshaller->ReadU8(msg))
        {
            ncMsg.EarSeperation = earSeperation.value();
        }
        else
        {
            return;
        }
        if (auto earRotation = this->marshaller->ReadU8(msg))
        {
            ncMsg.EarRotation = earRotation.value();
        }
        else
        {
            return;
        }
        if (auto earSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.EarSize = earSize.value();
        }
        else
        {
            return;
        }
        if (auto faceComplexion = this->marshaller->ReadU8(msg))
        {
            ncMsg.FaceComplexion = faceComplexion.value();
        }
        else
        {
            return;
        }
        if (auto faceDetails = this->marshaller->ReadU8(msg))
        {
            ncMsg.FaceDetails = faceDetails.value();
        }
        else
        {
            return;
        }
        if (auto faceExtraDetails = this->marshaller->ReadU8(msg))
        {
            ncMsg.FaceExtraDetails = faceExtraDetails.value();
        }
        else
        {
            return;
        }
        if (auto faceWrinkles = this->marshaller->ReadU8(msg))
        {
            ncMsg.FaceWrinkles = faceWrinkles.value();
        }
        else
        {
            return;
        }
        if (auto noseBridgeHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.NoseBridgeHeight = noseBridgeHeight.value();
        }
        else
        {
            return;
        }
        if (auto noseBridgeSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.NoseBridgeSize = noseBridgeSize.value();
        }
        else
        {
            return;
        }
        if (auto nosePosition = this->marshaller->ReadU8(msg))
        {
            ncMsg.NosePosition = nosePosition.value();
        }
        else
        {
            return;
        }
        if (auto noseTipHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.NoseTipHeight = noseTipHeight.value();
        }
        else
        {
            return;
        }
        if (auto noseTipSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.NoseTipSize = noseTipSize.value();
        }
        else
        {
            return;
        }
        if (auto nosetrilHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.NosetrilHeight = nosetrilHeight.value();
        }
        else
        {
            return;
        }
        if (auto nosetrilSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.NosetrilSize = nosetrilSize.value();
        }
        else
        {
            return;
        }
        if (auto jawHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.JawHeight = jawHeight.value();
        }
        else
        {
            return;
        }
        if (auto jawSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.JawSize = jawSize.value();
        }
        else
        {
            return;
        }
        if (auto chinHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChinHeight = chinHeight.value();
        }
        else
        {
            return;
        }
        if (auto chinWidth = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChinWidth = chinWidth.value();
        }
        else
        {
            return;
        }
        if (auto chinDepth = this->marshaller->ReadU8(msg))
        {
            ncMsg.ChinDepth = chinDepth.value();
        }
        else
        {
            return;
        }
        if (auto mouthType = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthType = mouthType.value();
        }
        else
        {
            return;
        }
        if (auto mouthPosition = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthPosition = mouthPosition.value();
        }
        else
        {
            return;
        }
        if (auto mouthSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthSize = mouthSize.value();
        }
        else
        {
            return;
        }
        if (auto mouthTopSize = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthTopSize = mouthTopSize.value();
        }
        else
        {
            return;
        }
        if (auto mouthCornerHeight = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthCornerHeight = mouthCornerHeight.value();
        }
        else
        {
            return;
        }
        if (auto mouthBottomScale = this->marshaller->ReadU8(msg))
        {
            ncMsg.MouthBottomScale = mouthBottomScale.value();
        }
        else
        {
            return;
        }
        if (auto skinColor = this->marshaller->ReadU8(msg))
        {
            ncMsg.SkinColor = skinColor.value();
        }
        else
        {
            return;
        }
        if (auto hairColor = this->marshaller->ReadU8(msg))
        {
            ncMsg.HairColor = hairColor.value();
        }
        else
        {
            return;
        }
        if (auto eyeColor = this->marshaller->ReadU8(msg))
        {
            ncMsg.EyeColor = eyeColor.value();
        }
        else
        {
            return;
        }
        if (auto lipsColor = this->marshaller->ReadU8(msg))
        {
            ncMsg.LipsColor = lipsColor.value();
        }
        else
        {
            return;
        }
        this->network->Dispatch(ncMsg);

        break;
    }
    case ClientMessageType::CharacterMove:
    {
        ActionMoveMessage cmMsg = ActionMoveMessage();
        if (auto x = this->marshaller->ReadFloat(msg))
        {
            cmMsg.OldX = x.value();
        }
        else
        {
            return;
        }
        if (auto y = this->marshaller->ReadFloat(msg))
        {
            cmMsg.OldY = y.value();
        }
        else
        {
            return;
        }
        if (auto z = this->marshaller->ReadFloat(msg))
        {
            cmMsg.OldZ = z.value();
        }
        else
        {
            return;
        }
        if (auto facing = this->marshaller->ReadFloat(msg))
        {
            cmMsg.Facing = facing.value();
        }
        else
        {
            return;
        }
        if (auto headpitch = this->marshaller->ReadFloat(msg))
        {
            cmMsg.HeadPitch = headpitch.value();
        }
        else
        {
            return;
        }
        if (auto headyaw = this->marshaller->ReadFloat(msg))
        {
            cmMsg.HeadYaw = headyaw.value();
        }
        else
        {
            return;
        }
        
        break;
    }
    default:
        break;
    }
}


