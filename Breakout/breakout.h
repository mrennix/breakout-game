#pragma once

// Generic function to check if two shapes are 
// intersecting (colliding)
template<typename T1, typename T2>
bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right()  >= mB.left()
        && mA.left()   <= mB.right()
        && mA.bottom() >= mB.top()
        && mA.top()    <= mB.bottom();
}