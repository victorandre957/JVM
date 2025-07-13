#include "OperationsBase.h"

#include "Frame.h"
#include "ArrayObject.h"
#include "ClassVisao.h"
#include "MethodArea.h"
#include "Stringobject.h"
#include "PilhaJVM.h"
#include "StaticClass.h"
#include "Utils.h"

OperationsBase::OperationsBase() :
		_isWide(false) {
}

OperationsBase::~OperationsBase() {

}

void OperationsBase::executarMetodos(StaticClass *classRuntime) {
	PilhaJVM &pilhaJVM = PilhaJVM::getInstance();

	vector<Value> arguments;
	Value commandLineArgs;
	commandLineArgs.type = ValueType::REFERENCE;
	commandLineArgs.data.object = new ArrayObject(ValueType::REFERENCE);
	arguments.push_back(commandLineArgs);

	pilhaJVM.addFrame(new Frame(classRuntime, "main", "([Ljava/lang/String;)V", arguments));

	if (verificarMetodoExiste(classRuntime, "<clinit>", "()V")) {
		pilhaJVM.addFrame(new Frame(classRuntime, "<clinit>", "()V", arguments));
	}

	while (pilhaJVM.size() > 0) {
		Frame *topFrame = pilhaJVM.getTopFrame();
		u1 *code = topFrame->getCode(topFrame->pc);
		// cerr << "codigo : " << (int)code[0] << " " << endl;
		executeInstruction(code[0]);
	}
}

bool OperationsBase::verificarMetodoExiste(StaticClass *classRuntime, string name, string descriptor) {
	ClassFile *classFile = classRuntime->getClassFile();

	bool found = false;
	method_info method;
	for (int i = 0; i < classFile->methods_count; i++) {
		method = classFile->methods[i];
		string methodName = Utils::getFormattedConstant(classFile->constant_pool, method.name_index);
		string methodDesc = Utils::getFormattedConstant(classFile->constant_pool, method.descriptor_index);

		if (methodName == name && methodDesc == descriptor) {
			found = true;
			break;
		}
	}

	return found;
}

void OperationsBase::populateMultiarray(ArrayObject *array, ValueType valueType, stack<int> count) {
	int currCount = count.top();
	count.pop();

	ValueType arrayType = (count.size() > 1) ? ValueType::REFERENCE : valueType;

	if (count.size() == 0) {
		for (int i = 0; i < currCount; i++) {
			Value subarrayValue;
			subarrayValue.type = valueType;
			subarrayValue.printType = valueType;
			subarrayValue.data.longValue = 0;
			array->pushValue(subarrayValue);
		}
	} else {
		for (int i = 0; i < currCount; i++) {
			ArrayObject *subarray = new ArrayObject(arrayType);
			populateMultiarray(subarray, valueType, count);

			Value subarrayValue;
			subarrayValue.type = ValueType::REFERENCE;
			subarrayValue.data.object = subarray;
			array->pushValue(subarrayValue);
		}
	}
}

void OperationsBase::nop() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->pc += 1;
}

void OperationsBase::wide() {
	_isWide = true;
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->pc += 1;
}
