//
// Created by LiShangyu on 2024/3/5.
//

#ifndef SVF_LIGHTANALYSIS_H
#define SVF_LIGHTANALYSIS_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <cstdio>

#include "SVFIR/SVFValue.h"
#include "SVFIR/SVFVariables.h"
#include "clang-c/Index.h"
#include <assert.h>

namespace SVF
{

class LightAnalysis
{

private:

    // the path of the directory that the source codes locate.
    // if the path is not a file, then must end with "/".
    std::string srcPath;

    std::string directFilePath;

    // we can get this from debug info of possible changes.
    std::string exactFile;

    /// Maintain the modification of lines, we do not delete lines, only increase lines.
    /// E.g. Table: line    offset
    ///               15         2  (from line 15, we add 2 lines)
    ///               17         3  (from line 17, we add 3 lines)
    std::map<int, int> lineOffsetMap;

public:

    LightAnalysis();

    LightAnalysis(const std::string&);

    ~LightAnalysis();

    // TODO: not sure about SVFValue or SVFVar, and the return type.
    // this function is used to map the SVFValue to its corresponding AST node.
    void projection(const SVFValue*, const SVFVar*);

    static enum CXChildVisitResult cursorVisitor(CXCursor cursor,
                                                 CXCursor parent,
                                                 CXClientData client_data);


    void runOnSrc();

    static int getLineFromSVFSrcLocString(const std::string&);

    static int getColumnFromSVFSrcLocString(const std::string&);

    static std::string getFileFromSVFSrcLocString(const std::string&);

    /// Only works for Intra, Call, Ret ICFGNodes.
    static const SVFInstruction* getInstFromICFGNode(const ICFGNode*);
};

}

#endif // SVF_LIGHTANALYSIS_H