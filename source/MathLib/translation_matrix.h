#ifndef translation_matrix_h
#define translation_matrix_h

namespace bde {
    /**
     * Constructs a translation matrix based on the given values.
     * @param x The translation along the x axis.
     * @param y The translation along the y axis.
     * @param z The translation along the z axis.
     */
    template<class Real>
    Matrix<4,4, Real> translation_matrix(const Real &x, const Real &y, const Real &z){
        return Matrix<4,4, Real>({
            1,0,0,x,
            0,1,0,y,
            0,0,1,z,
            0,0,0,1
        });
    }
    
    /**
     * Constructs a translation matrix based on the given translation vector.
     * @param translation The translation vector.
     */
    template<class Real>
    Matrix<4,4, Real> translation_matrix(const Vector<3, Real> &translation){
        return translation_matrix(translation[0],
                                  translation[1],
                                  translation[2]);
    }
} // namespace bde

#endif /* matrix_operations_h */
