#include "GenRotArea.h"
using namespace MR;

GenRotArea::GenRotArea(const char *pName) : AreaObj(pName) {
    mGo = true;
}

void GenRotArea::init(const JMapInfoIter &rIter) {
    AreaObj::init(rIter);
    connectToSceneAreaObj(this);
    connectToSceneMapObjMovement(this);
    getGeneratorID(rIter, &mGenID);
    getJMapInfoArg0NoInit(rIter, &mRot.x);
    getJMapInfoArg1NoInit(rIter, &mRot.y);
    getJMapInfoArg2NoInit(rIter, &mRot.z);

    AllLiveActorGroup* alag = getAllLiveActorGroup();
    s32 alSz = alag->mNumObjs;
    mGroup = new LiveActorGroup("GRAGroup", alSz);

    for (s32 i = 0; i < alSz; i++) {
        LiveActor* currActor = alag->getActor(i);
        s16 matchid = currActor->mLinkedInfo.mLinkId;
        s16 checkid = mGenID;
        OSReport("[GRA] Object: %s, mLinkID: %hd vs GenID: %hd\n", currActor->mName, matchid, checkid);
        if (matchid == checkid) {
            mGroup->registerActor(currActor);
            OSReport("[GRA] Added Object %d to mGroup\n", currActor->mName);
        }
    }
}

bool GenRotArea::rotater() {
    s32 x = 0; 
    s32 grpSz = mGroup->mNumObjs;
    if (grpSz < 1) return false;

    while (x < grpSz) {
        LiveActor *currAct = mGroup->getActor(x);
        currAct->mRotation += mRot;
        ++x;
    }
    
    if (x == grpSz) return true;
    else {
        OSReport("[GRA] Object amount inconsistent with amount rotated, failing. X: %d, GrpSz: %d\n", x, grpSz);
        return false;
    }
}

void GenRotArea::movement() {
    if (mGo && isInVolume(*getPlayerPos())) {
        mGo == false;

        rotater()
        ? OSReport("[GRA] Rotated %d objects with ID %hd\n", mGroup->mNumObjs, mGroup->getActor(0)->mLinkedInfo.mLinkId) 
        , OSReport("[GRA] Rotated by X: %d, Y: %d, Z: %d\n", mRot.x, mRot.y, mRot.z)
        : OSReport("[GRA] Failed Rotate or 0 objects found\n");
    }
}

const char* GenRotArea::getManagerName() const {
    return "GenRotArea";
}