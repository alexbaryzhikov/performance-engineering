; ModuleID = 'dax.c'
source_filename = "dax.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx13.0.0"

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @dax(double* noalias noundef %0, double noundef %1, double* noalias noundef %2, i64 noundef %3) #0 {
  %5 = alloca double*, align 8
  %6 = alloca double, align 8
  %7 = alloca double*, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  store double* %0, double** %5, align 8
  store double %1, double* %6, align 8
  store double* %2, double** %7, align 8
  store i64 %3, i64* %8, align 8
  store i64 0, i64* %9, align 8
  br label %10

10:                                               ; preds = %24, %4
  %11 = load i64, i64* %9, align 8
  %12 = load i64, i64* %8, align 8
  %13 = icmp slt i64 %11, %12
  br i1 %13, label %14, label %27

14:                                               ; preds = %10
  %15 = load double, double* %6, align 8
  %16 = load double*, double** %7, align 8
  %17 = load i64, i64* %9, align 8
  %18 = getelementptr inbounds double, double* %16, i64 %17
  %19 = load double, double* %18, align 8
  %20 = fmul double %15, %19
  %21 = load double*, double** %5, align 8
  %22 = load i64, i64* %9, align 8
  %23 = getelementptr inbounds double, double* %21, i64 %22
  store double %20, double* %23, align 8
  br label %24

24:                                               ; preds = %14
  %25 = load i64, i64* %9, align 8
  %26 = add nsw i64 %25, 1
  store i64 %26, i64* %9, align 8
  br label %10, !llvm.loop !10

27:                                               ; preds = %10
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.5a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 13, i32 3]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"branch-target-enforcement", i32 0}
!3 = !{i32 8, !"sign-return-address", i32 0}
!4 = !{i32 8, !"sign-return-address-all", i32 0}
!5 = !{i32 8, !"sign-return-address-with-bkey", i32 0}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 1}
!9 = !{!"Apple clang version 14.0.3 (clang-1403.0.22.14.1)"}
!10 = distinct !{!10, !11}
!11 = !{!"llvm.loop.mustprogress"}
