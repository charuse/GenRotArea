#pragma once
#include "syati.h"

struct Rotater {
    s32 x;
    s32 y;
    s32 z;
};

class GenRotArea : public AreaObj {
public:
    GenRotArea(const char *pName);

    virtual void init(const JMapInfoIter &rIter);
    virtual bool rotater();
    virtual void movement();
    virtual const char* getManagerName() const;

    LiveActorGroup* mGroup;
    Rotater mRot;
    s32 mGenID;
    bool mGo;
};