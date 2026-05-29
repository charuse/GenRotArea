#pragma once
#include "syati.h"

class GenRotArea : public AreaObj {
public:
    GenRotArea(const char *pName);

    virtual void init(const JMapInfoIter &rIter);
    virtual bool rotater();
    virtual void movement();
    virtual const char* getManagerName() const;

    LiveActorGroup* mGroup;
    TVec3f mRot;
    s32 mGenID;
    bool mGo;
};