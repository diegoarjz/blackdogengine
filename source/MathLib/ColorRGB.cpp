//
//  ColorRGB.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 12/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ColorRGB.h"
#include <string.h>

namespace bde {

    ColorRGB::ColorRGB() {
        mComponents[0] = 0;
        mComponents[1] = 0;
        mComponents[2] = 0;
    }

    ColorRGB::ColorRGB(F32 r, F32 g, F32 b) {
        mComponents[0]=r;
        mComponents[1]=g;
        mComponents[2]=b;
    }

    ColorRGB::ColorRGB(F32 components[3]) {
        mComponents[0]=components[0];
        mComponents[1]=components[1];
        mComponents[2]=components[2];
    }

    ColorRGB::ColorRGB(const ColorRGB &o) {
        mComponents[0]=o.mComponents[0];
        mComponents[1]=o.mComponents[1];
        mComponents[2]=o.mComponents[2];
    }

    ColorRGB &ColorRGB::operator=(const ColorRGB &o) {
        // No need to handle self assignment.
        mComponents[0]=o.mComponents[0];
        mComponents[1]=o.mComponents[1];
        mComponents[2]=o.mComponents[2];
        return *this;
    }

    bool ColorRGB::operator== (const ColorRGB &o) const {
        return
            mComponents[0] == o.mComponents[0] &&
            mComponents[1] == o.mComponents[1] &&
            mComponents[2] == o.mComponents[2];
    }

    bool ColorRGB::operator!= (const ColorRGB &o) const {
        return
            mComponents[0] != o.mComponents[0] ||
            mComponents[1] != o.mComponents[1] ||
            mComponents[2] != o.mComponents[2];
    }

    I32 ColorRGB::compareColors (const ColorRGB &o) const {
        return memcmp(mComponents,o.mComponents,3*sizeof(F32));
    }

    bool ColorRGB::operator< (const ColorRGB &o) const {
        return compareColors(o) < 0;
    }

    bool ColorRGB::operator<= (const ColorRGB &o) const {
        return compareColors(o) <= 0;
    }

    bool ColorRGB::operator> (const ColorRGB &o) const {
        return compareColors(o) > 0;
    }

    bool ColorRGB::operator>= (const ColorRGB &o) const {
        return compareColors(o) >= 0;
    }

    ColorRGB ColorRGB::operator+ (const ColorRGB &o) const {
        return ColorRGB(
                   mComponents[0] + o.mComponents[0],
                   mComponents[1] + o.mComponents[1],
                   mComponents[2] + o.mComponents[2]);
    }

    ColorRGB ColorRGB::operator- (const ColorRGB &o) const {
        return ColorRGB(
                   mComponents[0] - o.mComponents[0],
                   mComponents[1] - o.mComponents[1],
                   mComponents[2] - o.mComponents[2]);
    }

    ColorRGB ColorRGB::operator* (const ColorRGB &o) const {
        return ColorRGB(
                   mComponents[0]*o.mComponents[0],
                   mComponents[1]*o.mComponents[1],
                   mComponents[2]*o.mComponents[2]);
    }

    ColorRGB ColorRGB::operator* (F32 s) const {
        return ColorRGB(
                   s*mComponents[0],
                   s*mComponents[1],
                   s*mComponents[2]);
    }

    ColorRGB operator* (F32 s, const ColorRGB &o) {
        return ColorRGB(
                   s*o.mComponents[0],
                   s*o.mComponents[1],
                   s*o.mComponents[2]);
    }

    ColorRGB &ColorRGB::operator+= (const ColorRGB &o) {
        mComponents[0] += o.mComponents[0];
        mComponents[1] += o.mComponents[1];
        mComponents[2] += o.mComponents[2];
        return *this;
    }

    ColorRGB &ColorRGB::operator-= (const ColorRGB &o) {
        mComponents[0] -= o.mComponents[0];
        mComponents[1] -= o.mComponents[1];
        mComponents[2] -= o.mComponents[2];
        return *this;
    }

    ColorRGB &ColorRGB::operator*= (const ColorRGB &o) {
        mComponents[0] *= o.mComponents[0];
        mComponents[1] *= o.mComponents[1];
        mComponents[2] *= o.mComponents[2];
        return *this;
    }

    ColorRGB &ColorRGB::operator*= (F32 s) {
        mComponents[0] *= s;
        mComponents[1] *= s;
        mComponents[2] *= s;
        return *this;
    }

    void ColorRGB::Clamp () {
        for (U32 i = 0; i < 3; i++) {
            if (mComponents[i] > 1.0f) {
                mComponents[i] = 1.0f;
            }
            else if (mComponents[i] < 0.0f) {
                mComponents[i] = 0.0f;
            }
        }
    }

    void ColorRGB::ScaleByMax () {
        F32 fMax = mComponents[0];

        if (mComponents[1] > fMax) {
            fMax = mComponents[1];
        }

        if (mComponents[2] > fMax) {
            fMax = mComponents[2];
        }

        if (fMax > 1.0f) {
            F32 fInvMax = 1.0f/fMax;

            for (U32 i = 0; i < 3; i++) {
                mComponents[i] *= fInvMax;
            }
        }
    }

    std::ostream &operator<< (std::ostream &stream, const ColorRGB &o) {
        stream << "RGB[" << o.mComponents[0] << ", " << o.mComponents[1] << ", " <<
               o.mComponents[2] << "]";
        return stream;
    }

    ColorRGB::~ColorRGB() {
    }
}