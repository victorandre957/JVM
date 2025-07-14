#include "ClassVisao.h"
#include "Utils.h"

using namespace std;

// Instruction names array for bytecode display
static const char* const INSTRUCTION_NAMES[] = {
    "nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst_3", "iconst_4", "iconst_5",
    "lconst_0", "lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush",
    "ldc", "ldc_w", "ldc2_w", "iload", "lload", "fload", "dload", "aload", "iload_0", "iload_1", "iload_2",
    "iload_3", "lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3",
    "dload_0", "dload_1", "dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload",
    "laload", "faload", "daload", "aaload", "baload", "caload", "saload", "istore", "lstore", "fstore",
    "dstore", "astore", "istore_0", "istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2",
    "lstore_3", "fstore_0", "fstore_1", "fstore_2", "fstore_3", "dstore_0", "dstore_1", "dstore_2",
    "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore", "lastore", "fastore", "dastore",
    "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup", "dup_x1", "dup_x2", "dup2", "dup2_x1",
    "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd", "isub", "lsub", "fsub", "dsub", "imul", "lmul",
    "fmul", "dmul", "idiv", "ldiv", "fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg",
    "fneg", "dneg", "ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor",
    "ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i", "f2l", "f2d", "d2i", "d2l",
    "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl", "fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt",
    "ifge", "ifgt", "ifle", "if_icmpeq", "if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple",
    "if_acmpeq", "if_acmpne", "goto", "jsr", "ret", "tableswitch", "lookupswitch", "ireturn", "lreturn",
    "freturn", "dreturn", "areturn", "return", "getstatic", "putstatic", "getfield", "putfield",
    "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "UNUSED", "new", "newarray",
    "anewarray", "arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit",
    "wide", "multianewarray", "ifnull", "ifnonnull", "goto_w", "jsr_w"
};

// Helper function to get access flags string
static const char* getAccessFlagsString(u2 accessFlags) {
    static char buffer[256];
    buffer[0] = '\0';
    
    if (accessFlags & 0x0001) strcat(buffer, "public ");
    if (accessFlags & 0x0002) strcat(buffer, "private ");
    if (accessFlags & 0x0004) strcat(buffer, "protected ");
    if (accessFlags & 0x0008) strcat(buffer, "static ");
    if (accessFlags & 0x0010) strcat(buffer, "final ");
    if (accessFlags & 0x0020) strcat(buffer, "super ");
    if (accessFlags & 0x0040) strcat(buffer, "volatile ");
    if (accessFlags & 0x0080) strcat(buffer, "transient ");
    if (accessFlags & 0x0200) strcat(buffer, "interface ");
    if (accessFlags & 0x0400) strcat(buffer, "abstract ");
    
    // Remove trailing space
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == ' ') {
        buffer[len - 1] = '\0';
    }
    
    return buffer;
}

// Helper function to print tabs
static void printTabs(FILE* output, int count) {
    for (int i = 0; i < count; i++) {
        fprintf(output, "\t");
    }
}

// Function to display constant pool
static void displayConstantPool(ClassFile* classFile, FILE* output) {
    fprintf(output, "Constant Pool (count: %hu)\n", classFile->constant_pool_count);
    fprintf(output, "{\n");

    cp_info* constantPool = classFile->constant_pool;
    
    for (int i = 0; i < classFile->constant_pool_count - 1; i++) {
        const cp_info& element = constantPool[i];
        
        fprintf(output, "\t[%d] ", i + 1);
        
        switch (element.tag) {
            case CONSTANT_Class: {
                const CONSTANT_Class_info& classInfo = element.info.class_info;
                fprintf(output, "CONSTANT_Class_info\n");
                printTabs(output, 2);
                fprintf(output, "Class name: cp_info #%hu <%s>\n", classInfo.name_index,
                        Utils::getFormattedConstant(constantPool, classInfo.name_index));
                break;
            }
            case CONSTANT_Fieldref: {
                const CONSTANT_Fieldref_info& fieldRef = element.info.fieldref_info;
                fprintf(output, "CONSTANT_Fieldref_info\n");
                printTabs(output, 2);
                fprintf(output, "Class: cp_info #%hu <%s>\n", fieldRef.class_index,
                        Utils::getFormattedConstant(constantPool, fieldRef.class_index));
                printTabs(output, 2);
                fprintf(output, "Name and Type: cp_info #%hu <%s>\n", fieldRef.name_and_type_index,
                        Utils::getFormattedConstant(constantPool, fieldRef.name_and_type_index));
                break;
            }
            case CONSTANT_Methodref: {
                const CONSTANT_Methodref_info& methodRef = element.info.methodref_info;
                fprintf(output, "CONSTANT_Methodref_info\n");
                printTabs(output, 2);
                fprintf(output, "Class: cp_info #%hu <%s>\n", methodRef.class_index,
                        Utils::getFormattedConstant(constantPool, methodRef.class_index));
                printTabs(output, 2);
                fprintf(output, "Name and Type: cp_info #%hu <%s>\n", methodRef.name_and_type_index,
                        Utils::getFormattedConstant(constantPool, methodRef.name_and_type_index));
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                const CONSTANT_InterfaceMethodref_info& interfaceMethodRef = element.info.interfaceMethodref_info;
                fprintf(output, "CONSTANT_InterfaceMethodref_info\n");
                printTabs(output, 2);
                fprintf(output, "Class: cp_info #%hu <%s>\n", interfaceMethodRef.class_index,
                        Utils::getFormattedConstant(constantPool, interfaceMethodRef.class_index));
                printTabs(output, 2);
                fprintf(output, "Name and Type: cp_info #%hu <%s>\n", interfaceMethodRef.name_and_type_index,
                        Utils::getFormattedConstant(constantPool, interfaceMethodRef.name_and_type_index));
                break;
            }
            case CONSTANT_String: {
                const CONSTANT_String_info& stringInfo = element.info.string_info;
                fprintf(output, "CONSTANT_String_info\n");
                printTabs(output, 2);
                fprintf(output, "String: cp_info #%hu <%s>\n", stringInfo.string_index,
                        Utils::getFormattedConstant(constantPool, stringInfo.string_index));
                break;
            }
            case CONSTANT_Integer: {
                const CONSTANT_Integer_info& intInfo = element.info.integer_info;
                fprintf(output, "CONSTANT_Integer_info\n");
                printTabs(output, 2);
                fprintf(output, "Bytes: 0x%.8X\n", intInfo.bytes);
                printTabs(output, 2);
                fprintf(output, "Integer: %s\n", Utils::getFormattedConstant(constantPool, i + 1));
                break;
            }
            case CONSTANT_Float: {
                fprintf(output, "CONSTANT_Float_info\n");
                printTabs(output, 2);
                fprintf(output, "Float: %s\n", Utils::getFormattedConstant(constantPool, i + 1));
                break;
            }
            case CONSTANT_Long: {
                fprintf(output, "CONSTANT_Long_info\n");
                printTabs(output, 2);
                fprintf(output, "Long: %s\n", Utils::getFormattedConstant(constantPool, i + 1));
                i++; // Long constants take 2 slots
                break;
            }
            case CONSTANT_Double: {
                fprintf(output, "CONSTANT_Double_info\n");
                printTabs(output, 2);
                fprintf(output, "Double: %s\n", Utils::getFormattedConstant(constantPool, i + 1));
                i++; // Double constants take 2 slots
                break;
            }
            case CONSTANT_NameAndType: {
                const CONSTANT_NameAndType_info& nameType = element.info.nameAndType_info;
                fprintf(output, "CONSTANT_NameAndType_info\n");
                printTabs(output, 2);
                fprintf(output, "Name: cp_info #%hu <%s>\n", nameType.name_index,
                        Utils::getFormattedConstant(constantPool, nameType.name_index));
                printTabs(output, 2);
                fprintf(output, "Descriptor: cp_info #%hu <%s>\n", nameType.descriptor_index,
                        Utils::getFormattedConstant(constantPool, nameType.descriptor_index));
                break;
            }
            case CONSTANT_Utf8: {
                const CONSTANT_Utf8_info& utf8Info = element.info.utf8_info;
                fprintf(output, "CONSTANT_Utf8_info\n");
                printTabs(output, 2);
                fprintf(output, "Length: %hu\n", utf8Info.length);
                printTabs(output, 2);
                fprintf(output, "String: %s\n", Utils::getFormattedConstant(constantPool, i + 1));
                break;
            }
            default:
                fprintf(output, "CONSTANT_Unknown_info (tag=%d)\n", element.tag);
                break;
        }
    }
    
    fprintf(output, "}\n\n");
}

// Function to display bytecode
static void displayByteCode(const Code_attribute& code, cp_info* constantPool, FILE* output) {
    u4 code_length = code.code_length;
    u1* codeData = code.code;
    
    fprintf(output, "\t\tBytecode:\n");
    
    uint32_t lineNumber = 0;
    u4 i = 0;
    
    while (i < code_length) {
        printTabs(output, 3);
        
        u1 opcode = codeData[i];
        fprintf(output, "%d: %d ", lineNumber++, i);
        
        if (opcode < 202) { // Valid instruction range
            fprintf(output, "%s", INSTRUCTION_NAMES[opcode]);
        } else {
            fprintf(output, "unknown_%02x", opcode);
        }
        
        // Handle instruction operands with constant pool references
        if (opcode == 0x12) { // ldc
            u1 index = codeData[i + 1];
            fprintf(output, " #%d <%s>", index, Utils::getFormattedConstant(constantPool, index));
            i += 2;
        } else if (opcode == 0x13 || opcode == 0x14) { // ldc_w, ldc2_w
            u2 index = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " #%d <%s>", index, Utils::getFormattedConstant(constantPool, index));
            i += 3;
        } else if (opcode == 0x10) { // bipush
            fprintf(output, " %d", (int8_t)codeData[i + 1]);
            i += 2;
        } else if (opcode == 0x11) { // sipush
            int16_t value = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " %d", value);
            i += 3;
        } else if ((opcode >= 0x15 && opcode <= 0x19) || (opcode >= 0x36 && opcode <= 0x3a)) { // loads/stores with index
            fprintf(output, " %d", codeData[i + 1]);
            i += 2;
        } else if (opcode == 0x84) { // iinc
            fprintf(output, " %d by %d", codeData[i + 1], (int8_t)codeData[i + 2]);
            i += 3;
        } else if (opcode >= 0xb2 && opcode <= 0xb8) { // field/method references
            u2 index = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " #%d <%s>", index, Utils::getFormattedConstant(constantPool, index));
            i += 3;
        } else if (opcode == 0xb9) { // invokeinterface
            u2 index = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " #%d <%s> count %d", index, Utils::getFormattedConstant(constantPool, index), codeData[i + 3]);
            i += 5;
        } else if (opcode == 0xbb || opcode == 0xbd || opcode == 0xc0 || opcode == 0xc1) { // new, anewarray, checkcast, instanceof
            u2 index = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " #%d <%s>", index, Utils::getFormattedConstant(constantPool, index));
            i += 3;
        } else if (opcode >= 0x99 && opcode <= 0xa6) { // conditional jumps
            int16_t offset = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " %d (%+d)", i + offset, offset);
            i += 3;
        } else if (opcode == 0xa7 || opcode == 0xa8) { // goto, jsr
            int16_t offset = (codeData[i + 1] << 8) | codeData[i + 2];
            fprintf(output, " %d (%+d)", i + offset, offset);
            i += 3;
        } else {
            i += 1;
        }
        
        fprintf(output, "\n");
    }
}

// Function to display attributes
static void displayAttribute(const attribute_info& attr, cp_info* constantPool, FILE* output, int indentation) {
    const char* attributeName = Utils::getFormattedConstant(constantPool, attr.attribute_name_index);
    
    printTabs(output, indentation);
    fprintf(output, "Attribute: %s\n", attributeName);
    printTabs(output, indentation + 1);
    fprintf(output, "Attribute name index: cp_info #%d\n", attr.attribute_name_index);
    printTabs(output, indentation + 1);
    fprintf(output, "Attribute length: %d\n", attr.attribute_length);

    CONSTANT_Utf8_info attributeUtf8 = constantPool[attr.attribute_name_index - 1].info.utf8_info;
    
    if (Utils::compararUtf8String(attributeUtf8, "Code")) {
        const Code_attribute& code = attr.info.code_info;
        printTabs(output, indentation + 1);
        fprintf(output, "Maximum stack depth: %d\n", code.max_stack);
        printTabs(output, indentation + 1);
        fprintf(output, "Maximum local variables: %d\n", code.max_locals);
        printTabs(output, indentation + 1);
        fprintf(output, "Code length: %u\n", code.code_length);
        
        displayByteCode(code, constantPool, output);
        
        printTabs(output, indentation + 1);
        fprintf(output, "Exception table length: %d\n", code.exception_table_length);
        
        if (code.attributes_count > 0) {
            printTabs(output, indentation + 1);
            fprintf(output, "Attributes:\n");
            for (uint16_t i = 0; i < code.attributes_count; i++) {
                displayAttribute(code.attributes[i], constantPool, output, indentation + 2);
            }
        }
    } else if (Utils::compararUtf8String(attributeUtf8, "SourceFile")) {
        const SourceFile_attribute& sourceFile = attr.info.sourceFile_info;
        printTabs(output, indentation + 1);
        fprintf(output, "Source file: cp_info #%d <%s>\n", sourceFile.sourcefile_index,
                Utils::getFormattedConstant(constantPool, sourceFile.sourcefile_index));
    } else if (Utils::compararUtf8String(attributeUtf8, "LineNumberTable")) {
        const LineNumberTable_attribute& lineNumberTable = attr.info.lineNumberTable_info;
        printTabs(output, indentation + 1);
        fprintf(output, "Line number table length: %d\n", lineNumberTable.line_number_table_length);
        for (uint16_t i = 0; i < lineNumberTable.line_number_table_length; i++) {
            const LineNumberTable& entry = lineNumberTable.line_number_table[i];
            printTabs(output, indentation + 2);
            fprintf(output, "line %d: %d\n", entry.line_number, entry.start_pc);
        }
    }
}

// Main comprehensive class file display function
void printArquivoClassFile(ClassFile* classFile, FILE* output) {
    if (!classFile) {
        fprintf(output, "Error: ClassFile is null\n");
        return;
    }

    fprintf(output, "========== ClassFile Analysis ==========\n\n");
    
    // General Information
    fprintf(output, "General Information\n");
    fprintf(output, "{\n");
    fprintf(output, "\tMinor Version: %hu\n", classFile->minor_version);
    fprintf(output, "\tMajor Version: %hu [%.1f]\n", classFile->major_version, Utils::verificarVersao(classFile));
    fprintf(output, "\tConstant pool count: %hu\n", classFile->constant_pool_count);
    fprintf(output, "\tAccess Flags: 0x%.4X [%s]\n", classFile->access_flags, getAccessFlagsString(classFile->access_flags));
    fprintf(output, "\tThis class: cp_info #%hu <%s>\n", classFile->this_class,
            Utils::getFormattedConstant(classFile->constant_pool, classFile->this_class));
    
    if (classFile->super_class == 0) {
        fprintf(output, "\tSuper class: none\n");
    } else {
        fprintf(output, "\tSuper class: cp_info #%hu <%s>\n", classFile->super_class,
                Utils::getFormattedConstant(classFile->constant_pool, classFile->super_class));
    }
    
    fprintf(output, "\tInterfaces count: %hu\n", classFile->interfaces_count);
    fprintf(output, "\tFields count: %hu\n", classFile->fields_count);
    fprintf(output, "\tMethods count: %hu\n", classFile->methods_count);
    fprintf(output, "\tAttributes count: %hu\n", classFile->attributes_count);
    fprintf(output, "}\n\n");

    // Constant Pool
    displayConstantPool(classFile, output);

    // Interfaces
    if (classFile->interfaces_count > 0) {
        fprintf(output, "Interfaces (count: %hu)\n", classFile->interfaces_count);
        fprintf(output, "{\n");
        for (int i = 0; i < classFile->interfaces_count; i++) {
            fprintf(output, "\tInterface %d: cp_info #%hu <%s>\n", i, classFile->interfaces[i],
                    Utils::getFormattedConstant(classFile->constant_pool, classFile->interfaces[i]));
        }
        fprintf(output, "}\n\n");
    }

    // Fields
    if (classFile->fields_count > 0) {
        fprintf(output, "Fields (count: %hu)\n", classFile->fields_count);
        fprintf(output, "{\n");
        for (u2 i = 0; i < classFile->fields_count; i++) {
            const field_info& field = classFile->fields[i];
            fprintf(output, "\t[%hu] %s\n", i, Utils::getFormattedConstant(classFile->constant_pool, field.name_index));
            fprintf(output, "\t{\n");
            fprintf(output, "\t\tName: cp_info #%hu <%s>\n", field.name_index,
                    Utils::getFormattedConstant(classFile->constant_pool, field.name_index));
            fprintf(output, "\t\tDescriptor: cp_info #%hu <%s>\n", field.descriptor_index,
                    Utils::getFormattedConstant(classFile->constant_pool, field.descriptor_index));
            fprintf(output, "\t\tAccess flags: 0x%.4X [%s]\n", field.access_flags, getAccessFlagsString(field.access_flags));
            
            if (field.attributes_count > 0) {
                fprintf(output, "\t\tAttributes:\n");
                for (u2 j = 0; j < field.attributes_count; j++) {
                    displayAttribute(field.attributes[j], classFile->constant_pool, output, 3);
                }
            }
            fprintf(output, "\t}\n");
        }
        fprintf(output, "}\n\n");
    }

    // Methods
    if (classFile->methods_count > 0) {
        fprintf(output, "Methods (count: %hu)\n", classFile->methods_count);
        fprintf(output, "{\n");
        for (int i = 0; i < classFile->methods_count; i++) {
            const method_info& method = classFile->methods[i];
            fprintf(output, "\t[%d] %s\n", i, Utils::getFormattedConstant(classFile->constant_pool, method.name_index));
            fprintf(output, "\t{\n");
            fprintf(output, "\t\tName: cp_info #%d <%s>\n", method.name_index,
                    Utils::getFormattedConstant(classFile->constant_pool, method.name_index));
            fprintf(output, "\t\tDescriptor: cp_info #%d <%s>\n", method.descriptor_index,
                    Utils::getFormattedConstant(classFile->constant_pool, method.descriptor_index));
            fprintf(output, "\t\tAccess flags: 0x%.4X [%s]\n", method.access_flags, getAccessFlagsString(method.access_flags));
            
            if (method.attributes_count > 0) {
                fprintf(output, "\t\tAttributes:\n");
                for (int j = 0; j < method.attributes_count; j++) {
                    displayAttribute(method.attributes[j], classFile->constant_pool, output, 3);
                }
            }
            fprintf(output, "\t}\n");
        }
        fprintf(output, "}\n\n");
    }

    // Class Attributes
    if (classFile->attributes_count > 0) {
        fprintf(output, "Class Attributes (count: %hu)\n", classFile->attributes_count);
        fprintf(output, "{\n");
        for (uint16_t i = 0; i < classFile->attributes_count; i++) {
            displayAttribute(classFile->attributes[i], classFile->constant_pool, output, 1);
        }
        fprintf(output, "}\n\n");
    }

    fprintf(output, "========== End of Analysis ==========\n");
}

void exibeClassFile(ClassFile* classFile) {
    // Simply call the comprehensive file printer to stdout
    printArquivoClassFile(classFile, stdout);
}
