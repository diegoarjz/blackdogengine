#ifndef __BlackDogEngine__Transformation__
#define __BlackDogEngine__Transformation__

#include "MathLib/MathLib.h"

namespace bde {
    /**
     * Transformation between coordinate frames.
     */
    class Transformation{
    private:
        Quaternion mRotation;
        Vector3 mPosition;
        Vector3 mScale;
        Matrix4 mHomogeneousMatrix;
        bool mHomogeneousMatrixCurrent;
    public:
        
        const static Transformation Identity;
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Transformation();
        Transformation(const Vector3 &eulerAngles, const Vector3 &pos, const Vector3 &scale);
        Transformation(const Transformation& other);
        ~Transformation();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        void SetPosition(const float& x, const float& y, const float& z);
        void SetPosition(const Vector3 &pos);
        void Translate(const float& x, const float& y, const float& z);
        void Translate(const Vector3 &translation);
        
        // Rotation around Z axis
        void Yaw(const float& angle);
        // Rotation around Y axis
        void Pitch(const float& angle);
        // Rotation around X axis
        void Roll(const float& angle);
        
        void SetScale(const float& scale);
        void SetScale(const float& x, const float& y, const float& z);
        void SetScale(const Vector3 &s);
        
        Vector3 GetPosition()const;
        Vector3 GetScale()const;
        Quaternion GetRotation()const;
        void SetRotation(const Quaternion& rot);
        
        /* ***********
         * Operators *
         * **********/
        Transformation& operator=(const Transformation& other);
        bool operator==(const Transformation &other);
        bool operator!=(const Transformation &other);
        Transformation operator*(const Transformation &t2);
    }; // class Transformation
} // namespace bde
#endif /* defined(__BlackDogEngine__Transformation__) */
