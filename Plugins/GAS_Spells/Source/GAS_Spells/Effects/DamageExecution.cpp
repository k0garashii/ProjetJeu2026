#include "DamageExecution.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Data_SpellDamage, "Data.SpellDamage");

UDamageExecution::UDamageExecution()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UStatsSet, MagicalPower, Source, false);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UStatsSet, MagicalResistance, Target, false);
	
	RelevantAttributesToCapture.Add(MagicalPowerDef);
	RelevantAttributesToCapture.Add(MagicalResistanceDef);
}

void UDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	float MagicPow = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalPowerDef, EvaluationParameters, MagicPow);
	float MagicRes = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalResistanceDef, EvaluationParameters, MagicRes);
	const float SpellDamage = Spec.GetSetByCallerMagnitude(TAG_Data_SpellDamage, false, 0.f);
	
	float finalDamage = - FMath::Max(SpellDamage * MagicPow - MagicRes, 0);
	FGameplayModifierEvaluatedData datas = { UStatsSet::GetHealthAttribute(), EGameplayModOp::Additive, finalDamage };
	
	OutExecutionOutput.AddOutputModifier(datas);
}
