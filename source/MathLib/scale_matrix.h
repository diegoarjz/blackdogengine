#ifndef scale_matrix_h
#define scale_matrix_h

namespace bde {
    
    /**
     * Constructs and returns a scale matrix based on the given values.
     * @param x The scale along the x axis.
     * @param y The scale along the y axis.
     * @param z The scale alont the z axis.
     */
    template<class Real>
    Matrix<4,4, Real> scale_matrix(const Real &x, const Real &y, const Real& z){
        return Matrix<4,4, Real>({
            x,0,0,0,
            0,y,0,0,
            0,0,z,0,
            0,0,0,1
        });
    }
    
    /**
     * Constructs and returns a scale matrix based on the scale vector.
     * @param scale The scale vector.
     */
    template<class Real>
    Matrix<4,4, Real> scale_matrix(const Vector<3, Real> &scale){
        return scale_matrix(scale[0],
                            scale[1],
                            scale[2]);
    }
    
    /**
     * Constructs and returns a scale matrix with an
     * homogenous scale (equal along each axis).
     * @param homogeneous_scale The scale along all axis.
     */
    template<class Real>
    Matrix<4,4, Real> scale_matrix(const Real &homogeneous_scale){
        return scale_matrix(homogeneous_scale,
                            homogeneous_scale,
                            homogeneous_scale);
    }
    
} // namespace bde

#endif /* scale_matrix_h */
