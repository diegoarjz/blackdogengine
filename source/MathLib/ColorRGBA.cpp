//
//  ColorRGBA.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 12/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ColorRGBA.h"
#include <string.h>

namespace bde {
    ColorRGBA::ColorRGBA() {
        mComponents[0]=0;
        mComponents[1]=0;
        mComponents[2]=0;
        mComponents[3]=1;
    }

    ColorRGBA::ColorRGBA(F32 r, F32 g, F32 b, F32 a) {
        mComponents[0]=r;
        mComponents[1]=g;
        mComponents[2]=b;
        mComponents[3]=a;
    }

    ColorRGBA::ColorRGBA(F32 components[4]) {
        mComponents[0]=components[0];
        mComponents[1]=components[1];
        mComponents[2]=components[2];
        mComponents[3]=components[3];
    }

    ColorRGBA::ColorRGBA(const ColorRGBA &o) {
        mComponents[0]=o.mComponents[0];
        mComponents[1]=o.mComponents[1];
        mComponents[2]=o.mComponents[2];
        mComponents[3]=o.mComponents[3];
    }

    ColorRGBA &ColorRGBA::operator=(const ColorRGBA &o) {
        // No need to handle self assignment
        mComponents[0]=o.mComponents[0];
        mComponents[1]=o.mComponents[1];
        mComponents[2]=o.mComponents[2];
        mComponents[3]=o.mComponents[3];
        return *this;
    }



    bool ColorRGBA::operator== (const ColorRGBA &o) const {
        return
            mComponents[0] == o.mComponents[0] &&
            mComponents[1] == o.mComponents[1] &&
            mComponents[2] == o.mComponents[2] &&
            mComponents[3] == o.mComponents[3];
    }

    bool ColorRGBA::operator!= (const ColorRGBA &o) const {
        return
            mComponents[0] != o.mComponents[0] ||
            mComponents[1] != o.mComponents[1] ||
            mComponents[2] != o.mComponents[2] ||
            mComponents[3] != o.mComponents[3];
    }

    I32 ColorRGBA::compareColors (const ColorRGBA &o) const {
        return memcmp(mComponents,o.mComponents,3*sizeof(F32));
    }

    bool ColorRGBA::operator< (const ColorRGBA &o) const {
        return compareColors(o) < 0;
    }

    bool ColorRGBA::operator<= (const ColorRGBA &o) const {
        return compareColors(o) <= 0;
    }

    bool ColorRGBA::operator> (const ColorRGBA &o) const {
        return compareColors(o) > 0;
    }

    bool ColorRGBA::operator>= (const ColorRGBA &o) const {
        return compareColors(o) >= 0;
    }

    ColorRGBA ColorRGBA::operator+ (const ColorRGBA &o) const {
        return ColorRGBA(
                   mComponents[0] + o.mComponents[0],
                   mComponents[1] + o.mComponents[1],
                   mComponents[2] + o.mComponents[2],
                   mComponents[3] + o.mComponents[3]);
    }

    ColorRGBA ColorRGBA::operator- (const ColorRGBA &o) const {
        return ColorRGBA(
                   mComponents[0] - o.mComponents[0],
                   mComponents[1] - o.mComponents[1],
                   mComponents[2] - o.mComponents[2],
                   mComponents[3] - o.mComponents[3]);
    }

    ColorRGBA ColorRGBA::operator* (const ColorRGBA &o) const {
        return ColorRGBA(
                   mComponents[0]*o.mComponents[0],
                   mComponents[1]*o.mComponents[1],
                   mComponents[2]*o.mComponents[2],
                   mComponents[3] * o.mComponents[3]);
    }

    ColorRGBA ColorRGBA::operator* (F32 s) const {
        return ColorRGBA(
                   s*mComponents[0],
                   s*mComponents[1],
                   s*mComponents[2],
                   s*mComponents[3]);
    }

    ColorRGBA operator* (F32 s, const ColorRGBA &o) {
        return ColorRGBA(
                   s*o.mComponents[0],
                   s*o.mComponents[1],
                   s*o.mComponents[2],
                   s*o.mComponents[3]);
    }

    ColorRGBA &ColorRGBA::operator+= (const ColorRGBA &o) {
        mComponents[0] += o.mComponents[0];
        mComponents[1] += o.mComponents[1];
        mComponents[2] += o.mComponents[2];
        mComponents[3] += o.mComponents[3];
        return *this;
    }

    ColorRGBA &ColorRGBA::operator-= (const ColorRGBA &o) {
        mComponents[0] -= o.mComponents[0];
        mComponents[1] -= o.mComponents[1];
        mComponents[2] -= o.mComponents[2];
        mComponents[3] -= o.mComponents[3];
        return *this;
    }

    ColorRGBA &ColorRGBA::operator*= (const ColorRGBA &o) {
        mComponents[0] *= o.mComponents[0];
        mComponents[1] *= o.mComponents[1];
        mComponents[2] *= o.mComponents[2];
        mComponents[3] *= o.mComponents[3];
        return *this;
    }

    ColorRGBA &ColorRGBA::operator*= (F32 s) {
        mComponents[0] *= s;
        mComponents[1] *= s;
        mComponents[2] *= s;
        mComponents[3] *= s;
        return *this;
    }

    void ColorRGBA::Clamp () {
        for (U32 i = 0; i < 4; i++) {
            if (mComponents[i] > 1.0f) {
                mComponents[i] = 1.0f;
            }
            else if (mComponents[i] < 0.0f) {
                mComponents[i] = 0.0f;
            }
        }
    }

    void ColorRGBA::ScaleByMax () {
        F32 fMax = mComponents[0];

        if (mComponents[1] > fMax) {
            fMax = mComponents[1];
        }

        if (mComponents[2] > fMax) {
            fMax = mComponents[2];
        }

        if (mComponents[3] > fMax) {
            fMax = mComponents[3];
        }

        if (fMax > 1.0f) {
            F32 fInvMax = 1.0f/fMax;

            for (U32 i = 0; i < 3; i++) {
                mComponents[i] *= fInvMax;
            }
        }
    }

    std::ostream &operator<< (std::ostream &stream, const ColorRGBA &o) {
        stream << "RGBA[" << o.mComponents[0] << ", " << o.mComponents[1] << ", " <<
               o.mComponents[2] << ", " << o.mComponents[3] << "]";
        return stream;
    }

    ColorRGBA::~ColorRGBA() {
    }
}