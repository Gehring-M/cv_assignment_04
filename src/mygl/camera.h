#pragma once

#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/matrix4d.h>

#define BASE_FOV static_cast<float>(to_radians(45))
#define BASE_CAM_FOLLOW_OFFSET Vector3D(0.0, 5.0, -15.0)
#define BASE_CAM_POSITION Vector3D(100, 80, -40)

struct Camera
{
    float width;
    float height;
    float fov;
    float nearPlane;
    float farPlane;
    Vector3D position;
    Vector3D lookAt;
    Vector3D initUp;

    Matrix3D rotation = Matrix3D::identity();
};

/**
 * @brief Function to initialize a camera.
 *
 * @param width Image width.
 * @param height Image height.
 * @param fov Field of view (in rad).
 * @param nearPlane Plane defining closest points that get rendered.
 * @param farPlane Plane defining fardest points that get rendered.
 * @param initPos Initial position of camera.
 * @param lookAt Point at which the camera is looking at.
 * @param initUp Initial up direction of camera.
 *
 * @return Initialized camera object.
 */
Camera cameraCreate(float width, float height, float fov, float nearPlane, float farPlane, const Vector3D &initPos, const Vector3D &lookAt = {0, 0, 0}, const Vector3D &initUp = {0, 1, 0});

/**
 * @brief Get projection matrix from a camera.
 *
 * @param cam Camera from which the projection matrix is calculated.
 *
 * @return Projection matrix.
 */
Matrix4D cameraProjection(const Camera &cam);

/**
 * @brief Get view matrix from a camera.
 *
 * @param cam Camera from which the view matrix is calculated.
 *
 * @return View matrix.
 */
Matrix4D cameraView(const Camera &cam);

/**
 * @brief Get camera position in world space.
 *
 * @param cam Camera for which the position is returned.
 *
 * @return Camera position
 */
Vector3D cameraPosition(const Camera &cam);

/**
 * @brief Update camera position on the orbit around the look at point using spherical coordinates.
 *
 * @param cam Camera that gets updated.
 * @param mouseDiff X and Y distances that are used to change the spherical coordinate angles of the camera position.
 * with respect to the look at point.
 * @param zoom Factor to zoom in (-) or out (+) (distance of camera position to look at point is de-/increased).
 */
void cameraUpdateOrbit(Camera &cam, const Vector2D &mouseDiff, float zoom);

/**
 * @brief Updates camera lookAt and the camera position so that the distance between lookAt and the camera position
 * stays the same.
 *
 * @param cam Camera that gets updated.
 * @param pos New lookAt position.
 */
void cameraFollow(Camera &cam, const Vector3D &pos);

/**
 * @brief Updates camera rotation which is used to calculate the camera view.
 * 
 * @param cam Camera that gets updated.
 * @param rotation New rotation matrix.
 */
void setCameraRotation(Camera &cam, const Matrix3D &rotation);

/**
 * @brief Resets the camera's rotation matrix to the identity matrix.
 * 
 * @param cam Camera that gets updated.
 */
void resetCameraRotation(Camera &cam);
