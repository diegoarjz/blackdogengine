//
//  ColorRGBA.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 12/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef BlackDogEngine_ColorRGBA_h
#define BlackDogEngine_ColorRGBA_h

#include <iostream>

#include "../DataTypes.h"

namespace bde {
    /**
     * Represents RGBA colors.
     * It is an extension of ColorRGB which adds a fourth component (Alpha), indicating transparencies.
     * @see ColorRGB
     */
    class ColorRGBA{
    private:
        /// Color components.
        F32 mComponents[4];
    public:
        /* **************
         * CONSTRUCTORS *
         * *************/
        ColorRGBA();
        ColorRGBA (F32 r, F32 g, F32 b, F32 a);
        ColorRGBA (F32 components[4]);
        ColorRGBA (const ColorRGBA& o);
        
        /* ***********
         * ACCESSORS *
         * **********/
        F32 operator[] (U32 i) const;
        F32& operator[] (U32 i);
        F32 R () const;
        F32& R ();
        F32 G () const;
        F32& G ();
        F32 B () const;
        F32& B ();
        F32 A () const;
        F32& A ();
        
        /* ***********
         * OPERATORS *
         * **********/
        // Assignment
        ColorRGBA& operator=(const ColorRGBA& o);
        
        // Conversion
        operator const F32* () const;
        operator F32* ();
        
        // Comparison
        bool operator== (const ColorRGBA& rkC) const;
        bool operator!= (const ColorRGBA& rkC) const;
        bool operator<  (const ColorRGBA& rkC) const;
        bool operator<= (const ColorRGBA& rkC) const;
        bool operator>  (const ColorRGBA& rkC) const;
        bool operator>= (const ColorRGBA& rkC) const;
        
        // arithmetic operations
        ColorRGBA operator+ (const ColorRGBA& o) const;
        ColorRGBA operator- (const ColorRGBA& o) const;
        ColorRGBA operator* (const ColorRGBA& o) const;
        ColorRGBA operator* (F32 s) const;
        friend ColorRGBA operator* (F32 scalar, const ColorRGBA& o);
        
        
        // arithmetic updates
        ColorRGBA& operator+= (const ColorRGBA& o);
        ColorRGBA& operator-= (const ColorRGBA& o);
        ColorRGBA& operator*= (const ColorRGBA& o);
        ColorRGBA& operator*= (F32 s);
        
        
        
        /* *********
         * METHODS *
         * ********/
        /**
         * Transforms the color channels to [0,1]. Sets negative values to
         * zero and values larger than one to one.
         */
        void Clamp ();
        /**
         * Transforms the color channels to [0,1]. Assumes the color
         * channels are nonnegative, finds the maximum color channel, and divides
         * all channels by that value. Does not scale Alpha value.
         */
        void ScaleByMax ();
        
        /**
         * Output operation, mainly for debugging purposes.
         * @param stream [in] Output stream.
         * @param o [in] Color to output.
         * @return The stream parameter, allowing to chain operations.
         */
        friend std::ostream& operator<< (std::ostream& stream, const ColorRGBA& o);
        
        ~ColorRGBA();
        
    private:
        I32 compareColors (const ColorRGBA& rkC) const;
    };
    
    inline F32 ColorRGBA::R () const
    {
        return mComponents[0];
    }
    
    inline F32& ColorRGBA::R ()
    {
        return mComponents[0];
    }
    
    inline F32 ColorRGBA::G () const
    {
        return mComponents[1];
    }
    
    inline F32& ColorRGBA::G ()
    {
        return mComponents[1];
    }
    
    inline F32 ColorRGBA::B () const
    {
        return mComponents[2];
    }
    
    inline F32& ColorRGBA::B ()
    {
        return mComponents[2];
    }
    
    inline F32 ColorRGBA::A () const
    {
        return mComponents[3];
    }
    
    inline F32& ColorRGBA::A ()
    {
        return mComponents[3];
    }
    
    inline ColorRGBA::operator const F32* () const{
        return mComponents;
    }
    
    inline ColorRGBA::operator F32*(){
        return mComponents;
    }
    
    inline F32 ColorRGBA::operator[] (U32 i) const
    {
        return mComponents[i];
    }
    
    inline F32& ColorRGBA::operator[] (U32 i)
    {
        return mComponents[i];
    }
}

#else
namespace bde{
    class ColorRGBA;
}

#endif
