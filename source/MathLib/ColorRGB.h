#ifndef BlackDogEngine_ColorRGB_h
#define BlackDogEngine_ColorRGB_h

#include <iostream>

#include <cassert>

#include "../DataTypes.h"

namespace bde {
    /**
     * Represents a RGB color.
     *
     * Components are stored in an array of floats. Each component must be between 0 and 1.
     *
     * ## Access and Modification ##
     * There are a number of ways to modify the color components.
     *
     * - Using the index operator:
     *     ColorRGB c;
     *     c[0] = 1.0; // Defines the red component
     *     c[1] = 0.5; // Defines the green component
     *     c[2] = 0.3; // Defines the blue component
     *
     * - Using the named accessors:
     *     c.R() = 1.0;
     *     c.G() = 0.5;
     *     c.B() = 0.3;
     *
     * ## Color Comparison ##
     *
     * Color comparison is done using the memcmp c function and, as such, every byte of the
     * color components array is compared in sequence. If all bytes are equal, then the colors
     * are equal. Otherwise, color A > color B if the first unequal byte of A has a greater arithmetic
     * value than its counterpart in B. On the other hand, if it is smaller then A < B.
     */
    class ColorRGB {
      private:
        /// Stores the Red, Green and Blue components in that order.
        F32 mComponents[3];
      public:
        /* **************
         * Constructors *
         * *************/
        /**
         * Default constructor.
         * Initializes all components to 0, resulting in black.
         */
        ColorRGB();
        /**
         * Constructor specifying the components individually.
         * @param r [in] Red component.
         * @param g [in] Green component.
         * @param b [in] Blue component.
         */
        ColorRGB (F32 r, F32 g, F32 b);
        /**
         * Constructor specifying all components in an array.
         * @param components [in] Array of 3 floats specifying the red green and blue components.
         */
        ColorRGB (F32 components[3]);
        /**
         * Copy Constructor.
         * @param o [in] Another color Object.
         */
        ColorRGB (const ColorRGB &o);

        /* **********************
         * Acessors & Modifiers *
         * *********************/

        /**
         * Red Component accessor.
         * @return The red component.
         */
        F32 R () const;
        /**
         * Red Component accessor and modifier.
         * @return A reference to the red component, allowing it to be modified.
         */
        F32 &R ();
        /**
         * Green Component accessor.
         * @return The green component.
         */
        F32 G () const;
        /**
         * Green Component accessor and modifier.
         * @return A reference to the green component, allowing it to be modified.
         */
        F32 &G ();
        /**
         * Blue Component accessor.
         * @return The blue component.
         */
        F32 B () const;
        /**
         * Blue Component accessor and modifier.
         * @return A reference to the blue component, allowing it to be modified.
         */
        F32 &B ();

        /**
         * Access color components by index.
         * @param i [in] The index of the component: 0 - red, 1 - green, 2 - blue.
         * @param The component at index i.
         */
        F32 operator[] (U32 i) const;
        /**
         * Access and modify color components by index.
         * @param i [in] The index of the component: 0 - red, 1 - green, 2 - blue.
         * @param A reference to the component at index i, allowing it to be modified.
         */
        F32 &operator[] (U32 i);

        /* ***********
         * Operators *
         * **********/
        /**
         * Assignment Operator. Directly copies components from o to this color.
         * @param o The color to be copied.
         */
        ColorRGB &operator=(const ColorRGB &o);
        /**
         * Converts the object into a constant array of floats containing the color components.
         * @return A pointer to an array of floats containing the color components.
         */
        operator const F32 *() const;
        /**
         * Converts the object into an array of floats containing the color components.
         * @return A pointer to an array of floats containing the color components.
         */
        operator F32 *();

        /* **********************
         * Comparison Operators *
         * *********************/
        bool operator== (const ColorRGB &rkC) const;
        bool operator!= (const ColorRGB &rkC) const;
        bool operator<  (const ColorRGB &rkC) const;
        bool operator<= (const ColorRGB &rkC) const;
        bool operator>  (const ColorRGB &rkC) const;
        bool operator>= (const ColorRGB &rkC) const;

        /* ***********************
         * Arithmetic Operations *
         * **********************/
        ColorRGB operator+ (const ColorRGB &o) const;
        ColorRGB operator- (const ColorRGB &o) const;
        ColorRGB operator* (const ColorRGB &o) const;
        ColorRGB operator* (F32 s) const;
        friend ColorRGB operator* (F32 scalar, const ColorRGB &o);

        /* ********************
         * Arithmetic Updates *
         * *******************/
        ColorRGB &operator+= (const ColorRGB &o);
        ColorRGB &operator-= (const ColorRGB &o);
        ColorRGB &operator*= (const ColorRGB &o);
        ColorRGB &operator*= (F32 s);

        /**
         * Transforms the color channels to [0,1]. Sets negative values to
         * zero and values larger than one to one.
         */
        void Clamp ();

        /**
        * Transforms the color channels to [0,1]. Assumes the color
        * channels are nonnegative, finds the maximum color channel, and divides
        * all channels by that value.
        */
        void ScaleByMax ();

        /**
         * Output operation, mainly for debugging purposes.
         * @param stream [in] Output stream.
         * @param o [in] Color to output.
         * @return The stream parameter, allowing to chain operations.
         */
        friend std::ostream &operator<< (std::ostream &stream, const ColorRGB &o);

        ~ColorRGB();
      private:
        /**
         * Uses the memcmp function to compare colors.
         */
        I32 compareColors (const ColorRGB &rkC) const;
    };

    inline ColorRGB::operator const F32 *() const {
        return mComponents;
    }

    inline ColorRGB::operator F32 *() {
        return mComponents;
    }

    inline F32 ColorRGB::operator[] (U32 i) const {
        assert(0 <= i && i <= 2);
        return mComponents[i];
    }

    inline F32 &ColorRGB::operator[] (U32 i) {
        assert(0 <= i && i <= 2);
        return mComponents[i];
    }

    inline F32 ColorRGB::R () const {
        return mComponents[0];
    }

    inline F32 &ColorRGB::R () {
        return mComponents[0];
    }

    inline F32 ColorRGB::G () const {
        return mComponents[1];
    }

    inline F32 &ColorRGB::G () {
        return mComponents[1];
    }

    inline F32 ColorRGB::B () const {
        return mComponents[2];
    }

    inline F32 &ColorRGB::B () {
        return mComponents[2];
    }
}

#else
namespace bde {
    class ColorRGB;
}

#endif
