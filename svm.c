module_param(avic, int, S_IRUGO);
#endif

/* enable/disable Virtual VMLOAD VMSAVE */
static int vls = true;
module_param(vls, int, 0444);

/* AVIC VM ID bit masks and lock */
static DECLARE_BITMAP(avic_vm_id_bitmap, AVIC_VM_ID_NR);
static DEFINE_SPINLOCK(avic_vm_id_lock);
@@ -1093,6 +1097,16 @@ static __init int svm_hardware_setup(void)
		}
	}

	if (vls) {
		if (!npt_enabled ||
		    !boot_cpu_has(X86_FEATURE_VIRTUAL_VMLOAD_VMSAVE) ||
		    !IS_ENABLED(CONFIG_X86_64)) {
			vls = false;
		} else {
			pr_info("Virtual VMLOAD VMSAVE supported\n");
		}
	}

	return 0;

err:
@@ -1280,6 +1294,16 @@ static void init_vmcb(struct vcpu_svm *svm)
	if (avic)
		avic_init_vmcb(svm);

	/*
	 * If hardware supports Virtual VMLOAD VMSAVE then enable it
	 * in VMCB and clear intercepts to avoid #VMEXIT.
	 */
	if (vls) {
		clr_intercept(svm, INTERCEPT_VMLOAD);
		clr_intercept(svm, INTERCEPT_VMSAVE);
		svm->vmcb->control.virt_ext |= VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK;
	}

	mark_all_dirty(svm->vmcb);

	enable_gif(svm);