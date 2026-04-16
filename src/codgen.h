#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Vectorize.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

class PTXCodeGenerator : public ASTVisitor {
private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;
    
    // Current function being processed
    llvm::Function* currentFunction = nullptr;
    
    // Symbol tables
    std::unordered_map<std::string, llvm::Value*> namedValues;
    std::unordered_map<std::string, llvm::Value*> registers;
    std::unordered_map<std::string, llvm::Value*> parameters;
    std::unordered_map<std::string, llvm::BasicBlock*> labels;
    
    // Last processed value (for expression evaluation)
    llvm::Value* lastValue = nullptr;
    
    // Helper methods
    llvm::Type* getPTXType(const std::string& ptxType);
    llvm::Value* getBuiltinVar(const std::string& name);
    llvm::Value* generateVectorOp(const std::string& opcode, 
                                  const std::vector<llvm::Value*>& operands,
                                  const std::vector<std::string>& modifiers);
    bool isFloatingPointOperation(const std::string& opcode, const std::vector<llvm::Value*>& operands);


public:
    PTXCodeGenerator();
    
    void generateCode(Module* ast);
    
    // Visitor methods
    void visit(IntLiteral* node) override;
    void visit(FloatLiteral* node) override;
    void visit(StringLiteral* node) override;
    void visit(Identifier* node) override;
    void visit(Register* node) override;
    void visit(MemoryAccess* node) override;
    void visit(Parameter* node) override;
    void visit(BuiltinVar* node) override;
    void visit(Instruction* node) override;
    void visit(Label* node) override;
    void visit(BranchInst* node) override;
    void visit(ReturnInst* node) override;
    void visit(RegDecl* node) override;
    void visit(ParamDecl* node) override;
    void visit(Function* node) override;
    void visit(Module* node) override;
    
    // Utility methods
    void dumpModule();
    bool verifyModule();
    void optimizeModule();
    void generateRISCVAssembly(const std::string& filename);
};

#endif // CODEGEN_H
