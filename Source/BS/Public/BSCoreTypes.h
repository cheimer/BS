#pragma once
#include "Engine/DataTable.h"
#include "BSCoreTypes.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogSetting, Log, All);
//DEFINE_LOG_CATEGORY(LogSetting);

// Attack

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Melee = 0,
	Arrow,
	Spell
};

UENUM(BlueprintType)
enum class EAttackMaterial : uint8
{
	Thunder = 0,
	Water,
	Fire,
	Ice,
	Shine,
	Dark
};

UENUM(BlueprintType)
enum class EEnemyList : uint8
{
	Ghoul = 0,
	Goblin,
	Rich,
	SkelBow,
	SkelSword,
	Zombie
};

USTRUCT(BlueprintType)
struct FAttackState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	EAttackType AttackType = EAttackType::Melee;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	int32 AttackLevel = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float DamageDefault = 10.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float AttackDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (ToolTip = "Under 0 is Unlimited", EditCondition = "AttackType == EAttackType::Arrow"))
	int32 EnemyHitNum = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (EditCondition = "AttackType == EAttackType::Melee"))
	float AuraSize = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (EditCondition = "AttackType == EAttackType::Melee"))
	float AuraDefaultSize = AuraSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (EditCondition = "AttackType == EAttackType::Spell"))
	float SpellSize = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (EditCondition = "AttackType == EAttackType::Spell"))
	float SpellDefaultSize = 100.0f;

};

// Enemy

USTRUCT(BlueprintType)
struct FEnemyState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float Speed = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (ToolTip = "Recommend X5"))
	int32 DefaultDropMaterial = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (ToolTip = "Recommend X5"))
	int32 DefaultDropCoin = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float DropMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float SearchRange = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float AttackRange = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float AttackDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	EAttackType AttackType = EAttackType::Melee;

};

// Animation

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}
};
