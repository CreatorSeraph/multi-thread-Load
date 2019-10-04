#pragma once
#include "Component.h"

enum ColliderType : char
{
	MeshSphere,
	spriteBox,
};


struct Sphere
{
	Sphere() {}
	Sphere(float radius) : length(radius) {}

	Vector3 center;
	float length;

};

class Collider :
	public Component
{
private:

	ColliderType type;
	RECT* c_rect;
	Sphere* c_sphere;


public:
	Collider(ColliderType _type, float width, float height);
	Collider(ColliderType _type, float radius);
	Collider();

	virtual ~Collider();

	ColliderType GetColliderType() { return type; }
	RECT GetWorldRange();

	Vector3 GetCenter()
	{
		Vector3 diff = c_sphere->center;
		return diff;
	}
	float getlength()
	{
		return c_sphere->length;
	}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;


	//bool IsCollision(Collider* a, Collider* b);
};

/*

class Collider :
   public Component
{
   enum ColliderType
   {
      None,
      Box,
      Sphere
   };

   struct SphereData
   {
      SphereData() {}
      SphereData(float radius) : length(radius) {}

      Vector3 center;
      float length;

      static bool IsCollision(const SphereData* a, const SphereData* b);

      void Translation(const Vector3& center);
   };

   struct AABBData
   {
      AABBData() {}
      AABBData(float x, float y, float z)
         : localMin(-x / 2.f, -y / 2.f, -z / 2.f), localMax(x / 2.f, y / 2.f, z / 2.f) {}

      Vector3 localMin;
      Vector3 localMax;

      Vector3 center;

      Vector3 GetMin() const { return localMin + center; }
      Vector3 GetMax() const { return localMax + center; }

      static bool IsCollision(const AABBData* a, const AABBData* b);

      void Translation(const Vector3& center);
   };

   struct MixData
   {
      static bool IsCollision(const AABBData* a, const SphereData* b);
      static bool IsCollision(const SphereData* a, const AABBData* b);
   };

private:

   SphereData* sphereData = nullptr;
   AABBData* aabbData = nullptr;

   ColliderType type = None;

public:
   // Component을(를) 통해 상속됨
   virtual void Init();
   virtual void Update();
   virtual void Destroy();

   void SetAsSphere(float radius);
   void SetAsBox(float x, float y, float z);

public:
   static bool IsCollision(const Collider* col1, const Collider* col2);
};
*/