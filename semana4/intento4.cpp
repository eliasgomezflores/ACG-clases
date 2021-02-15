#include <stdio.h>
 
void WaitForEnter()
{
    printf("Press Enter to quit");
    fflush(stdin);
    getchar();
}
 
float mix(float a, float b, float t)
{
    // degree 1
    return a * (1.0f - t) + b*t;
}
 
float BezierQuadratic(float A, float B, float C, float t)
{
    // degree 2
    float AB = mix(A, B, t);
    float BC = mix(B, C, t);
    return mix(AB, BC, t);
}
 
float BezierCubic(float A, float B, float C, float D, float t)
{
    // degree 3
    float ABC = BezierQuadratic(A, B, C, t);
    float BCD = BezierQuadratic(B, C, D, t);
    return mix(ABC, BCD, t);
}
 
float BezierQuartic(float A, float B, float C, float D, float E, float t)
{
    // degree 4
    float ABCD = BezierCubic(A, B, C, D, t);
    float BCDE = BezierCubic(B, C, D, E, t);
    return mix(ABCD, BCDE, t);
}
 
float BezierQuintic(float A, float B, float C, float D, float E, float F, float t)
{
    // degree 5
    float ABCDE = BezierQuartic(A, B, C, D, E, t);
    float BCDEF = BezierQuartic(B, C, D, E, F, t);
    return mix(ABCDE, BCDEF, t);
}
 
float BezierSextic(float A, float B, float C, float D, float E, float F, float G, float t)
{
    // degree 6
    float ABCDEF = BezierQuintic(A, B, C, D, E, F, t);
    float BCDEFG = BezierQuintic(B, C, D, E, F, G, t);
    return mix(ABCDEF, BCDEFG, t);
}
 
int main(int argc, char **argv)
{
    struct SPoint
    {
        float x;
        float y;
    };
 
    SPoint controlPoints[7] =
    {
        { 0.0f, 1.1f },
        { 2.0f, 8.3f },
        { 0.5f, 6.5f },
        { 5.1f, 4.7f },
        { 3.3f, 3.1f },
        { 1.4f, 7.5f },
        { 2.1f, 0.0f },
    };
 
    //calculate some points on a sextic curve!
    const float c_numPoints = 10;
    for (int i = 0; i < c_numPoints; ++i)
    {
        float t = ((float)i) / (float(c_numPoints - 1));
        SPoint p;
        p.x = BezierSextic(controlPoints[0].x, controlPoints[1].x, controlPoints[2].x, controlPoints[3].x, controlPoints[4].x, controlPoints[5].x, controlPoints[6].x, t);
        p.y = BezierSextic(controlPoints[0].y, controlPoints[1].y, controlPoints[2].y, controlPoints[3].y, controlPoints[4].y, controlPoints[5].y, controlPoints[6].y, t);
        printf("point at time %0.2f = (%0.2f, %0.2f)n", t, p.x, p.y);
    }
 
    WaitForEnter();
}
