#ifndef __BlackDogEngine__Transformation__
#define __BlackDogEngine__Transformation__

#include "MathLib/Vector3.h"
#include "MathLib/Vector4.h"
#include "MathLib/Matrix3.h"
#include "MathLib/Matrix4.h"
#include "MathLib/Quaternion.h"

namespace bde {
    /**
     * Transformation between coordinate frames.
     */
    class Transformation{
    private:
        Quaternionf mRotation;
        Vector3f mPosition;
        Vector3f mScale;
        Matrix4f mHomogeneousMatrix;
        bool mHomogeneousMatrixCurrent;
    public:
        
        const static Transformation Identity;
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Transformation();
        Transformation(const Vector3f &eulerAngles, const Vector3f &pos, const Vector3f &scale);
        Transformation(const Transformation& other);
        ~Transformation();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        void SetPosition(const float& x, const float& y, const float& z);
        void SetPosition(const Vector3f &pos);
        void Translate(const float& x, const float& y, const float& z);
        void Translate(const Vector3f &translation);
        
        // Rotation around Z axis
        void Yaw(const float& angle);
        // Rotation around Y axis
        void Pitch(const float& angle);
        // Rotation around X axis
        void Roll(const float& angle);
        
        void SetScale(const float& scale);
        void SetScale(const float& x, const float& y, const float& z);
        void SetScale(const Vector3f &s);
        
        Vector3f GetPosition()const;
        Vector3f GetScale()const;
        Quaternionf GetRotation()const;
        void SetRotation(const Quaternionf& rot);
        
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
