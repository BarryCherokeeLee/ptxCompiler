#include "ast.h"
#include <iostream>
#include <iomanip>

static void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
}

void IntLiteral::print(int indent) const {
    printIndent(indent);
    std::cout << "IntLiteral: " << value << std::endl;
}

void IntLiteral::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void FloatLiteral::print(int indent) const {
    printIndent(indent);
    std::cout << "FloatLiteral: " << value << std::endl;
}

void FloatLiteral::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void StringLiteral::print(int indent) const {
    printIndent(indent);
    std::cout << "StringLiteral: \"" << value << "\"" << std::endl;
}

void StringLiteral::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Identifier::print(int indent) const {
    printIndent(indent);
    std::cout << "Identifier: " << name << std::endl;
}

void Identifier::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Register::print(int indent) const {
    printIndent(indent);
    std::cout << "Register: %" << name;
    if (index >= 0) std::cout << "<" << index << ">";
    std::cout << " (type: " << type << ")" << std::endl;
}

void Register::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void MemoryAccess::print(int indent) const {
    printIndent(indent);
    std::cout << "MemoryAccess:" << std::endl;
    address->print(indent + 1);
}

void MemoryAccess::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Parameter::print(int indent) const {
    printIndent(indent);
    std::cout << "Parameter: [" << name << "]" << std::endl;
}

void Parameter::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void BuiltinVar::print(int indent) const {
    printIndent(indent);
    std::cout << "BuiltinVar: %" << name << std::endl;
}

void BuiltinVar::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Instruction::print(int indent) const {
    printIndent(indent);
    std::cout << "Instruction: " << opcode;
    for (const auto& mod : modifiers) {
        std::cout << "." << mod;
    }
    std::cout << std::endl;
    
    for (const auto& operand : operands) {
        operand->print(indent + 1);
    }
}

void Instruction::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Label::print(int indent) const {
    printIndent(indent);
    std::cout << "Label: " << name << std::endl;
}

void Label::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void BranchInst::print(int indent) const {
    printIndent(indent);
    std::cout << "Branch: ";
    if (condition) {
        std::cout << "@" << (negated ? "!" : "");
        condition->print(0);
    }
    std::cout << " -> " << target << std::endl;
}

void BranchInst::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void ReturnInst::print(int indent) const {
    printIndent(indent);
    std::cout << "Return" << std::endl;
}

void ReturnInst::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void RegDecl::print(int indent) const {
    printIndent(indent);
    std::cout << "RegDecl: ." << type << " %" << name << "<" << count << ">" << std::endl;
}

void RegDecl::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void ParamDecl::print(int indent) const {
    printIndent(indent);
    std::cout << "ParamDecl: ." << type << " " << name << std::endl;
}

void ParamDecl::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Function::print(int indent) const {
    printIndent(indent);
    std::cout << "Function: " << visibility << " " << type << " " << name << std::endl;
    
    printIndent(indent + 1);
    std::cout << "Parameters:" << std::endl;
    for (const auto& param : parameters) {
        param->print(indent + 2);
    }
    
    printIndent(indent + 1);
    std::cout << "Registers:" << std::endl;
    for (const auto& reg : registers) {
        reg->print(indent + 2);
    }
    
    printIndent(indent + 1);
    std::cout << "Body:" << std::endl;
    for (const auto& stmt : body) {
        stmt->print(indent + 2);
    }
}

void Function::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}

void Module::print(int indent) const {
    printIndent(indent);
    std::cout << "Module:" << std::endl;
    printIndent(indent + 1);
    std::cout << "Version: " << version << std::endl;
    printIndent(indent + 1);
    std::cout << "Target: " << target << std::endl;
    printIndent(indent + 1);
    std::cout << "Address Size: " << address_size << std::endl;
    
    for (const auto& func : functions) {
        func->print(indent + 1);
    }
}

void Module::accept(ASTVisitor* visitor) {
    visitor->visit(this);
}
