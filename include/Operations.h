#ifndef executionengine_h
#define executionengine_h

#include "OperationsBase.h"
#include "OperationsConstants.h"
#include "OperationsLoadStore.h"
#include "OperationsArithmetic.h"
#include "OperationsControl.h"
#include "OperationsObject.h"

using namespace std;

class Operations;
typedef void (Operations::*funcaoGenericaPointeiro)();

/** @class Operations
 * @brief É responsável por realizar a execução do .class
 * @brief Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class Operations : public OperationsBase {
public:
	/**
	 * @brief Obter a única instância da Execution Engine.
	 * @return A instância da Execution Engine.
	 */
	static Operations& getInstance() {
		static Operations instance;
		return instance;
	}

	/**
	 * @brief Destrutor padrão.
	 */
	~Operations();

protected:
	/**
	 * @brief Implementa a execução de uma instrução baseada no opcode.
	 * @param opcode O código da instrução a ser executada.
	 */
	void executeInstruction(u1 opcode) override;

	/**
	 * @brief Inicializa a tabela de ponteiros para funções de instruções.
	 */
	void initInstructions() override;

private:
	/**
	 * @brief Construtor padrão.
	 */
	Operations();

	Operations(Operations const&); // não permitir implementação do construtor de cópia
	void operator=(Operations const&); // não permitir implementação do operador de igual

	/**
	 * Array de ponteiros para funções de instruções JVM.
	 */
	funcaoGenericaPointeiro funcaoGenerica[202];

	// Operation modules as composition
	OperationsConstants constantsOps;
	OperationsLoadStore loadStoreOps;
	OperationsArithmetic arithmeticOps;
	OperationsControl controlOps;
	OperationsObject objectOps;

	// Forward all instruction calls to appropriate modules
	void aconst_null() { constantsOps.aconst_null(); }
	void iconst_m1() { constantsOps.iconst_m1(); }
	void iconst_0() { constantsOps.iconst_0(); }
	void iconst_1() { constantsOps.iconst_1(); }
	void iconst_2() { constantsOps.iconst_2(); }
	void iconst_3() { constantsOps.iconst_3(); }
	void iconst_4() { constantsOps.iconst_4(); }
	void iconst_5() { constantsOps.iconst_5(); }
	void lconst_0() { constantsOps.lconst_0(); }
	void lconst_1() { constantsOps.lconst_1(); }
	void fconst_0() { constantsOps.fconst_0(); }
	void fconst_1() { constantsOps.fconst_1(); }
	void fconst_2() { constantsOps.fconst_2(); }
	void dconst_0() { constantsOps.dconst_0(); }
	void dconst_1() { constantsOps.dconst_1(); }
	void bipush() { constantsOps.bipush(); }
	void sipush() { constantsOps.sipush(); }
	void ldc() { constantsOps.ldc(); }
	void ldc_w() { constantsOps.ldc_w(); }
	void ldc2_w() { constantsOps.ldc2_w(); }

	// Load/Store operations
	void iload() { loadStoreOps.iload(); }
	void lload() { loadStoreOps.lload(); }
	void fload() { loadStoreOps.fload(); }
	void dload() { loadStoreOps.dload(); }
	void aload() { loadStoreOps.aload(); }
	void iload_0() { loadStoreOps.iload_0(); }
	void iload_1() { loadStoreOps.iload_1(); }
	void iload_2() { loadStoreOps.iload_2(); }
	void iload_3() { loadStoreOps.iload_3(); }
	void lload_0() { loadStoreOps.lload_0(); }
	void lload_1() { loadStoreOps.lload_1(); }
	void lload_2() { loadStoreOps.lload_2(); }
	void lload_3() { loadStoreOps.lload_3(); }
	void fload_0() { loadStoreOps.fload_0(); }
	void fload_1() { loadStoreOps.fload_1(); }
	void fload_2() { loadStoreOps.fload_2(); }
	void fload_3() { loadStoreOps.fload_3(); }
	void dload_0() { loadStoreOps.dload_0(); }
	void dload_1() { loadStoreOps.dload_1(); }
	void dload_2() { loadStoreOps.dload_2(); }
	void dload_3() { loadStoreOps.dload_3(); }
	void aload_0() { loadStoreOps.aload_0(); }
	void aload_1() { loadStoreOps.aload_1(); }
	void aload_2() { loadStoreOps.aload_2(); }
	void aload_3() { loadStoreOps.aload_3(); }
	void iaload() { loadStoreOps.iaload(); }
	void laload() { loadStoreOps.laload(); }
	void faload() { loadStoreOps.faload(); }
	void daload() { loadStoreOps.daload(); }
	void aaload() { loadStoreOps.aaload(); }
	void baload() { loadStoreOps.baload(); }
	void caload() { loadStoreOps.caload(); }
	void saload() { loadStoreOps.saload(); }
	void istore() { loadStoreOps.istore(); }
	void lstore() { loadStoreOps.lstore(); }
	void fstore() { loadStoreOps.fstore(); }
	void dstore() { loadStoreOps.dstore(); }
	void astore() { loadStoreOps.astore(); }
	void istore_0() { loadStoreOps.istore_0(); }
	void istore_1() { loadStoreOps.istore_1(); }
	void istore_2() { loadStoreOps.istore_2(); }
	void istore_3() { loadStoreOps.istore_3(); }
	void lstore_0() { loadStoreOps.lstore_0(); }
	void lstore_1() { loadStoreOps.lstore_1(); }
	void lstore_2() { loadStoreOps.lstore_2(); }
	void lstore_3() { loadStoreOps.lstore_3(); }
	void fstore_0() { loadStoreOps.fstore_0(); }
	void fstore_1() { loadStoreOps.fstore_1(); }
	void fstore_2() { loadStoreOps.fstore_2(); }
	void fstore_3() { loadStoreOps.fstore_3(); }
	void dstore_0() { loadStoreOps.dstore_0(); }
	void dstore_1() { loadStoreOps.dstore_1(); }
	void dstore_2() { loadStoreOps.dstore_2(); }
	void dstore_3() { loadStoreOps.dstore_3(); }
	void astore_0() { loadStoreOps.astore_0(); }
	void astore_1() { loadStoreOps.astore_1(); }
	void astore_2() { loadStoreOps.astore_2(); }
	void astore_3() { loadStoreOps.astore_3(); }
	void iastore() { loadStoreOps.iastore(); }
	void lastore() { loadStoreOps.lastore(); }
	void fastore() { loadStoreOps.fastore(); }
	void dastore() { loadStoreOps.dastore(); }
	void aastore() { loadStoreOps.aastore(); }
	void bastore() { loadStoreOps.bastore(); }
	void castore() { loadStoreOps.castore(); }
	void sastore() { loadStoreOps.sastore(); }

	// Arithmetic operations  
	void pop() { arithmeticOps.pop(); }
	void pop2() { arithmeticOps.pop2(); }
	void dup() { arithmeticOps.dup(); }
	void dup_x1() { arithmeticOps.dup_x1(); }
	void dup_x2() { arithmeticOps.dup_x2(); }
	void dup2() { arithmeticOps.dup2(); }
	void dup2_x1() { arithmeticOps.dup2_x1(); }
	void dup2_x2() { arithmeticOps.dup2_x2(); }
	void swap() { arithmeticOps.swap(); }
	void iadd() { arithmeticOps.iadd(); }
	void ladd() { arithmeticOps.ladd(); }
	void fadd() { arithmeticOps.fadd(); }
	void dadd() { arithmeticOps.dadd(); }
	void isub() { arithmeticOps.isub(); }
	void lsub() { arithmeticOps.lsub(); }
	void fsub() { arithmeticOps.fsub(); }
	void dsub() { arithmeticOps.dsub(); }
	void imul() { arithmeticOps.imul(); }
	void lmul() { arithmeticOps.lmul(); }
	void fmul() { arithmeticOps.fmul(); }
	void dmul() { arithmeticOps.dmul(); }
	void idiv() { arithmeticOps.idiv(); }
	void ldiv() { arithmeticOps.ldiv(); }
	void fdiv() { arithmeticOps.fdiv(); }
	void ddiv() { arithmeticOps.ddiv(); }
	void irem() { arithmeticOps.irem(); }
	void lrem() { arithmeticOps.lrem(); }
	void frem() { arithmeticOps.frem(); }
	void drem() { arithmeticOps.drem(); }
	void ineg() { arithmeticOps.ineg(); }
	void lneg() { arithmeticOps.lneg(); }
	void fneg() { arithmeticOps.fneg(); }
	void dneg() { arithmeticOps.dneg(); }
	void ishl() { arithmeticOps.ishl(); }
	void lshl() { arithmeticOps.lshl(); }
	void ishr() { arithmeticOps.ishr(); }
	void lshr() { arithmeticOps.lshr(); }
	void iushr() { arithmeticOps.iushr(); }
	void lushr() { arithmeticOps.lushr(); }
	void iand() { arithmeticOps.iand(); }
	void land() { arithmeticOps.land(); }
	void ior() { arithmeticOps.ior(); }
	void lor() { arithmeticOps.lor(); }
	void ixor() { arithmeticOps.ixor(); }
	void lxor() { arithmeticOps.lxor(); }
	void iinc() { arithmeticOps.iinc(); }
	void i2l() { arithmeticOps.i2l(); }
	void i2f() { arithmeticOps.i2f(); }
	void i2d() { arithmeticOps.i2d(); }
	void l2i() { arithmeticOps.l2i(); }
	void l2f() { arithmeticOps.l2f(); }
	void l2d() { arithmeticOps.l2d(); }
	void f2i() { arithmeticOps.f2i(); }
	void f2l() { arithmeticOps.f2l(); }
	void f2d() { arithmeticOps.f2d(); }
	void d2i() { arithmeticOps.d2i(); }
	void d2l() { arithmeticOps.d2l(); }
	void d2f() { arithmeticOps.d2f(); }
	void i2b() { arithmeticOps.i2b(); }
	void i2c() { arithmeticOps.i2c(); }
	void i2s() { arithmeticOps.i2s(); }
	void lcmp() { arithmeticOps.lcmp(); }
	void fcmpl() { arithmeticOps.fcmpl(); }
	void fcmpg() { arithmeticOps.fcmpg(); }
	void dcmpl() { arithmeticOps.dcmpl(); }
	void dcmpg() { arithmeticOps.dcmpg(); }

	// Control flow operations
	void ifeq() { controlOps.ifeq(); }
	void ifne() { controlOps.ifne(); }
	void iflt() { controlOps.iflt(); }
	void ifge() { controlOps.ifge(); }
	void ifgt() { controlOps.ifgt(); }
	void ifle() { controlOps.ifle(); }
	void if_icmpeq() { controlOps.if_icmpeq(); }
	void if_icmpne() { controlOps.if_icmpne(); }
	void if_icmplt() { controlOps.if_icmplt(); }
	void if_icmpge() { controlOps.if_icmpge(); }
	void if_icmpgt() { controlOps.if_icmpgt(); }
	void if_icmple() { controlOps.if_icmple(); }
	void if_acmpeq() { controlOps.if_acmpeq(); }
	void if_acmpne() { controlOps.if_acmpne(); }
	void func_goto() { controlOps.func_goto(); }
	void jsr() { controlOps.jsr(); }
	void ret() { controlOps.ret(); }
	void tableswitch() { controlOps.tableswitch(); }
	void lookupswitch() { controlOps.lookupswitch(); }
	void ireturn() { controlOps.ireturn(); }
	void lreturn() { controlOps.lreturn(); }
	void freturn() { controlOps.freturn(); }
	void dreturn() { controlOps.dreturn(); }
	void areturn() { controlOps.areturn(); }
	void func_return() { controlOps.func_return(); }
	void ifnull() { controlOps.ifnull(); }
	void ifnonnull() { controlOps.ifnonnull(); }
	void goto_w() { controlOps.goto_w(); }
	void jsr_w() { controlOps.jsr_w(); }

	// Object operations
	void getstatic() { objectOps.getstatic(); }
	void putstatic() { objectOps.putstatic(); }
	void getfield() { objectOps.getfield(); }
	void putfield() { objectOps.putfield(); }
	void invokevirtual() { objectOps.invokevirtual(); }
	void invokespecial() { objectOps.invokespecial(); }
	void invokestatic() { objectOps.invokestatic(); }
	void invokeinterface() { objectOps.invokeinterface(); }
	void func_new() { objectOps.func_new(); }
	void newarray() { objectOps.newarray(); }
	void anewarray() { objectOps.anewarray(); }
	void arraylength() { objectOps.arraylength(); }
	void athrow() { objectOps.athrow(); }
	void checkcast() { objectOps.checkcast(); }
	void instanceof() { objectOps.instanceof(); }
	void monitorenter() { objectOps.monitorenter(); }
	void monitorexit() { objectOps.monitorexit(); }
	void multianewarray() { objectOps.multianewarray(); }
	void wide() { OperationsBase::wide(); }
};

#endif /* executionengine_h */
