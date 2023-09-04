//
// Created by Loïc Barthe on 26/03/2020.
//

#ifndef TEST_DEFORMER2DBLENDMAX_H
#define TEST_DEFORMER2DBLENDMAX_H

#include "Deformer2D.h"

class Deformer2DBlendMax : public Deformer2D {


public:

    Deformer2DBlendMax ();

    Deformer2DBlendMax (DecaleScalarField2D *f1, unsigned int index1, DecaleScalarField2D *f2, unsigned int index2);

    double eval (double x, double y);

protected:

    double evalInner (double x, double y);

};


#endif //TEST_DEFORMER2DBLENDMAX_H
