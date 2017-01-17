// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = StartingHealth;
};
