#include "bbox.h"

double BBox::getArea( void ) const
{
    double l = ( max_.x - min_.x );
    double m = ( max_.y - min_.y );
    double n = ( max_.z - min_.z );
    return 2.0 * ( l * ( m + n ) + m * n );
}

bool BBox::intersect( const Ray &ray ) const
{

    double tmin;
    double tmax;
    double tymin;
    double tymax;
    double tzmin;
    double tzmax;
    double divx;
    double divy;
    double divz;

    divx = 1.0 / ray.direction_.x;
    if ( divx >= 0.0 )
    {
        tmin = ( min_.x - ray.origin_.x ) * divx;
        tmax = ( max_.x - ray.origin_.x ) * divx;
    }
    else
    {
        tmin = ( max_.x - ray.origin_.x ) * divx;
        tmax = ( min_.x - ray.origin_.x ) * divx;
    }

    divy = 1.0 / ray.direction_.y;
    if ( divy >= 0.0 )
    {
        tymin = ( min_.y - ray.origin_.y ) * divy;
        tymax = ( max_.y - ray.origin_.y ) * divy;
    }
    else
    {
        tymin = ( max_.y - ray.origin_.y ) * divy;
        tymax = ( min_.y - ray.origin_.y ) * divy;
    }

    if ( ( tmin > tymax ) || ( tymin > tmax ) )
        return false;

    if ( tymin > tmin )
        tmin = tymin;

    if ( tymax < tmax )
        tmax = tymax;

    divz = 1.0 / ray.direction_.z;
    if ( divz >= 0.0 )
    {
        tzmin = ( min_.z - ray.origin_.z ) * divz;
        tzmax = ( max_.z - ray.origin_.z ) * divz;
    }
    else
    {
        tzmin = ( max_.z - ray.origin_.z ) * divz;
        tzmax = ( min_.z - ray.origin_.z ) * divz;
    }

    if ( ( tmin > tzmax ) || ( tzmin > tmax ) )
        return false;

    if ( tzmin > tmin )
        tmin = tzmin;

    if ( tzmax < tmax )
        tmax  = tzmax;

    return true;//tmax > 0.00001;
}