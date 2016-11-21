<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>BaseTest.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BaseTest_8cpp</filename>
    <includes id="BaseTest_8h" name="BaseTest.h" local="yes" imported="no">BaseTest.h</includes>
  </compound>
  <compound kind="file">
    <name>BaseTest.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BaseTest_8h</filename>
  </compound>
  <compound kind="file">
    <name>BoundMap.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BoundMap_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>BoundMapHelpers.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BoundMapHelpers_8cpp</filename>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BOUNDMAPHELPERS_CPP</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a6195bc00deaaf7ee9bbfe797d6aa9c2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a9d8e073fb764e46fa6cbc46e807f6e17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>abb71bbacef76693dc99c5b2450a5d76d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>BoundMap</type>
      <name>getUnion</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a94e1bb574f5985fe3e3a9ed3b62f6dcd</anchor>
      <arglist>(const BoundMap &amp;map1, const BoundMap &amp;map2)</arglist>
    </member>
    <member kind="function">
      <type>BoundMap</type>
      <name>getIntersection</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a46b806b68715b9137435d84f2b9f307c</anchor>
      <arglist>(const BoundMap &amp;map1, const BoundMap &amp;map2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printBoundMap</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>afd2a7346e84534bbb6a668808518db22</anchor>
      <arglist>(const BoundMap &amp;map)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>intervalVecToString</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a287bd6151bfbfd5ec5058baedaf44da2</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; vec)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>valVecToString</name>
      <anchorfile>BoundMapHelpers_8cpp.shtml</anchorfile>
      <anchor>a36b4c894dc71bb1f3ae079ab75370ba1</anchor>
      <arglist>(const std::vector&lt; SCIP_Real &gt; vec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BranchControlFirst.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BranchControlFirst_8cpp</filename>
    <includes id="BranchControlFirst_8h" name="BranchControlFirst.h" local="yes" imported="no">BranchControlFirst.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_BRANCHEXECLP</name>
      <anchorfile>BranchControlFirst_8cpp.shtml</anchorfile>
      <anchor>abaae5b6bafdfda09184b033b0cf271ab</anchor>
      <arglist>(BranchruleControlFirst::scip_execlp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_BRANCHEXECEXT</name>
      <anchorfile>BranchControlFirst_8cpp.shtml</anchorfile>
      <anchor>a0b374e2f0b351ecbbd801366d88df684</anchor>
      <arglist>(BranchruleControlFirst::scip_execext)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_BRANCHEXECPS</name>
      <anchorfile>BranchControlFirst_8cpp.shtml</anchorfile>
      <anchor>a2726d81d3ae7893921e88ed3ca667e50</anchor>
      <arglist>(BranchruleControlFirst::scip_execps)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BranchControlFirst.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>BranchControlFirst_8h</filename>
  </compound>
  <compound kind="file">
    <name>ConstRateEvaluator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ConstRateEvaluator_8cpp</filename>
    <includes id="ConstRateEvaluator_8h" name="ConstRateEvaluator.h" local="yes" imported="no">ConstRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>ConstRateEvaluator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ConstRateEvaluator_8h</filename>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>CopyablePointer.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>CopyablePointer_8cpp</filename>
    <includes id="CopyablePointer_8h" name="CopyablePointer.h" local="yes" imported="no">CopyablePointer.h</includes>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a830c0cc2a0d855492067dd906ffe3ec3</anchor>
      <arglist>(std::ostream &amp;Str, CopyablePointer&lt; T &gt; const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a1b263dd419e5a3ca20368a3ff2697ea4</anchor>
      <arglist>(CopyablePointer&lt; T &gt; &amp;lhs, CopyablePointer&lt; T &gt; &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CopyablePointer.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>CopyablePointer_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>cppmain.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>cppmain_8cpp</filename>
    <includes id="reader__osilc_8h" name="reader_osilc.h" local="yes" imported="no">reader_osilc.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PropOBRA_8h" name="PropOBRA.h" local="yes" imported="no">PropOBRA.h</includes>
    <includes id="HeurSimODE_8h" name="HeurSimODE.h" local="yes" imported="no">HeurSimODE.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>cppmain_8cpp.shtml</anchorfile>
      <anchor>a3c04138a5bfe5d72780bb7e82a18e627</anchor>
      <arglist>(int argc, char **argv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ExprLookup.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ExprLookup_8cpp</filename>
    <includes id="ExprLookup_8h" name="ExprLookup.h" local="yes" imported="no">ExprLookup.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPREVAL</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a048a9e0fb65a33711566f88fd70c5aa4</anchor>
      <arglist>(evaluateLookup)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRINTEVAL</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>ac5f2a3226c076a4cb8df9668ff753b39</anchor>
      <arglist>(intervalEvaluateLookup)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRCURV</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a6d2c26390fa800937ab505d683928b3b</anchor>
      <arglist>(checkLookupCurvature)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRPROP</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>aad53b0e0253b250872dfc39ac08b7c31</anchor>
      <arglist>(propagateLookup)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRPRINT</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a8b213173cd8fcd6d81a0b89bccc6695b</anchor>
      <arglist>(lookupExprPrint)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRCOPYDATA</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>abcdb63c4f7bcbfcdde69b658779d3bb5</anchor>
      <arglist>(copyLookupExpr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_USEREXPRFREEDATA</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a60aa9424de9c5a292ea2a01fd272cae9</anchor>
      <arglist>(freeLookupExpr)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPexprCreateLookup</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a3a014ad60dd054bc11246a5a4ad13f76</anchor>
      <arglist>(BMS_BLKMEM *blkmem, SCIP_EXPR **expr, SCIP_EXPR *child, const shared_ptr&lt; spline::BSplineCurve&lt; 3, SCIP_Real &gt; &gt; &amp;spline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprLookupSetEpsilon</name>
      <anchorfile>ExprLookup_8cpp.shtml</anchorfile>
      <anchor>a8e7aa398d0b544e5d737498a196701c7</anchor>
      <arglist>(SCIP_Real epsilon)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ExprLookup.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ExprLookup_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPexprCreateLookup</name>
      <anchorfile>ExprLookup_8h.shtml</anchorfile>
      <anchor>a237af163a1c19ff3eeac18c38696623e</anchor>
      <arglist>(BMS_BLKMEM *blkmem, SCIP_EXPR **expr, SCIP_EXPR *child, const boost::shared_ptr&lt; spline::BSplineCurve&lt; 3, SCIP_Real &gt; &gt; &amp;spline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprLookupSetEpsilon</name>
      <anchorfile>ExprLookup_8h.shtml</anchorfile>
      <anchor>a8e7aa398d0b544e5d737498a196701c7</anchor>
      <arglist>(SCIP_Real epsilon)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ExprPiecewiseLinear.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ExprPiecewiseLinear_8cpp</filename>
    <includes id="ExprPiecewiseLinear_8h" name="ExprPiecewiseLinear.h" local="yes" imported="no">ExprPiecewiseLinear.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>EXPR_PCW_LIN_TEST_ESTIMATIONS</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a00ec8eff9b821735e7b94c1a9d7fd1b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Side</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>UPPER</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00ae704d5d328a8522a6193aa3efb28c724</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>LOWER</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00aa1017e9b343135a54a98b6f479354d16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>UPPER</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00ae704d5d328a8522a6193aa3efb28c724</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>LOWER</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00aa1017e9b343135a54a98b6f479354d16</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SAFE_ESTIMATOR</type>
      <name>selectEstimator</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a9a413471dc3a46e18d2ed4f9970dc09b</anchor>
      <arglist>(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Bool e5valid, SCIP_Bool e6valid)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setRoundingModeFromBool</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>ab76105fe1cf6e499efc1379be4401be7</anchor>
      <arglist>(SCIP_Bool mup)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>estimateSafe</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a2aa83ad4f431a89a12cc48a3fc18ffea</anchor>
      <arglist>(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Real y1, SCIP_Real y2, SAFE_ESTIMATOR estimator, SCIP_Real *coefficient, SCIP_Real *intercept)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPexprCreatePiecewiseLinear</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a6cab1baf9bcdd4cc7784bab58175e7ea</anchor>
      <arglist>(BMS_BLKMEM *blkmem, SCIP_EXPR **expr, SCIP_EXPR *child, const shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt; &amp;pcwlin, std::string identifier)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprPiecewiseLinearSetEpsilon</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a281e8a31d4a8c49a6d486361b17df380</anchor>
      <arglist>(SCIP_Real epsilon)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprPiecewiseLinearPrintPoints</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>a7be71a16b0bbd3add35cf583dd1a15da</anchor>
      <arglist>(SCIP_USEREXPRDATA *data, SCIP_MESSAGEHDLR *messagehdlr, FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt;</type>
      <name>SCIPexprPiecewiseLinearGetSpline</name>
      <anchorfile>ExprPiecewiseLinear_8cpp.shtml</anchorfile>
      <anchor>acf5995e1fc1ece9fcd73761ec73d14be</anchor>
      <arglist>(SCIP_USEREXPRDATA *data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ExprPiecewiseLinear.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ExprPiecewiseLinear_8h</filename>
    <includes id="TestExprPiecewiseLinear_8h" name="TestExprPiecewiseLinear.h" local="yes" imported="no">TestExprPiecewiseLinear.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>EXPR_PCW_LIN_TEST_ESTIMATIONS</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a00ec8eff9b821735e7b94c1a9d7fd1b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SAFE_ESTIMATOR</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_1</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9da4f19ad4a707e38d41fe48cd28f72b176</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_2</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9dae3822ca9d2ee2dc76a5601cc075d9927</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_3</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9dabe42500ec6952c9539395b794e2939c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_4</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9da2bdf4f768d433dbb46a1158dd08e0f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_5</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9da3c18f99905d953c02eae5cc7a48e4e8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SAFE_ESTIMATOR_TYPE_6</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a5e2d0f7d0ab5ddf96a8af02ca12b5a9da5a22827e8ab95756b97ee08926a12bcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPexprCreatePiecewiseLinear</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a411ed72aad1da5ca0be6fa10defbe57e</anchor>
      <arglist>(BMS_BLKMEM *blkmem, SCIP_EXPR **expr, SCIP_EXPR *child, const boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt; &amp;pcwlin, std::string identifier)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprPiecewiseLinearSetEpsilon</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a281e8a31d4a8c49a6d486361b17df380</anchor>
      <arglist>(SCIP_Real epsilon)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SCIPexprPiecewiseLinearPrintPoints</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a7be71a16b0bbd3add35cf583dd1a15da</anchor>
      <arglist>(SCIP_USEREXPRDATA *data, SCIP_MESSAGEHDLR *messagehdlr, FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>SAFE_ESTIMATOR</type>
      <name>selectEstimator</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a9a413471dc3a46e18d2ed4f9970dc09b</anchor>
      <arglist>(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Bool e5valid, SCIP_Bool e6valid)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>estimateSafe</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>a2aa83ad4f431a89a12cc48a3fc18ffea</anchor>
      <arglist>(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Real y1, SCIP_Real y2, SAFE_ESTIMATOR estimator, SCIP_Real *coefficient, SCIP_Real *intercept)</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt;</type>
      <name>SCIPexprPiecewiseLinearGetSpline</name>
      <anchorfile>ExprPiecewiseLinear_8h.shtml</anchorfile>
      <anchor>acf5995e1fc1ece9fcd73761ec73d14be</anchor>
      <arglist>(SCIP_USEREXPRDATA *data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>HeurSimODE.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HeurSimODE_8cpp</filename>
    <includes id="HeurSimODE_8h" name="HeurSimODE.h" local="yes" imported="no">HeurSimODE.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEURFREE</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>a23c0d4940c8d60e3a9d7c3708a539630</anchor>
      <arglist>(HeurSimODE::scip_free)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEURINIT</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>a2efb9e90604a9c8b262ab88a635e794c</anchor>
      <arglist>(HeurSimODE::scip_init)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEUREXIT</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>a4dd7ffc45f7cb2cea2331644f783a468</anchor>
      <arglist>(HeurSimODE::scip_exit)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEURINITSOL</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>acd70833116a32df813ad0776a0c156b8</anchor>
      <arglist>(HeurSimODE::scip_initsol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEUREXITSOL</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>ac265ed58fa2a0a145a6fe2fed865d8f1</anchor>
      <arglist>(HeurSimODE::scip_exitsol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEUREXEC</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>aca08098011bb3803de43098d60b7ca53</anchor>
      <arglist>(HeurSimODE::scip_exec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_HEURCLONE</name>
      <anchorfile>HeurSimODE_8cpp.shtml</anchorfile>
      <anchor>a7c2d389dbaa57fdfbe1100ba8fc70f5d</anchor>
      <arglist>(scip::ObjCloneable *HeurSimODE::clone)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>HeurSimODE.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HeurSimODE_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="ReduceODEintegrator_8hpp" name="ReduceODEintegrator.hpp" local="yes" imported="no">ReduceODEintegrator.hpp</includes>
    <includes id="Statistics_8h" name="Statistics.h" local="yes" imported="no">Statistics.h</includes>
  </compound>
  <compound kind="file">
    <name>HyperCube.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HyperCube_8cpp</filename>
    <includes id="HyperCube_8h" name="HyperCube.h" local="yes" imported="no">HyperCube.h</includes>
  </compound>
  <compound kind="file">
    <name>HyperCube.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HyperCube_8h</filename>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="Line_8h" name="Line.h" local="yes" imported="no">Line.h</includes>
    <includes id="Orthant_8h" name="Orthant.h" local="yes" imported="no">Orthant.h</includes>
    <includes id="OrthantList_8h" name="OrthantList.h" local="yes" imported="no">OrthantList.h</includes>
    <includes id="HyperPlane_8h" name="HyperPlane.h" local="yes" imported="no">HyperPlane.h</includes>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>HyperPlane.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HyperPlane_8cpp</filename>
    <includes id="HyperPlane_8h" name="HyperPlane.h" local="yes" imported="no">HyperPlane.h</includes>
  </compound>
  <compound kind="file">
    <name>HyperPlane.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>HyperPlane_8h</filename>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
  </compound>
  <compound kind="file">
    <name>IntervalODEintegrator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>IntervalODEintegrator_8cpp</filename>
    <includes id="IntervalODEintegrator_8h" name="IntervalODEintegrator.h" local="yes" imported="no">IntervalODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>IntervalODEintegrator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>IntervalODEintegrator_8h</filename>
    <includes id="ODEintegrator_8h" name="ODEintegrator.h" local="yes" imported="no">ODEintegrator.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="ConstRateEvaluator_8h" name="ConstRateEvaluator.h" local="yes" imported="no">ConstRateEvaluator.h</includes>
    <includes id="SimRateEvaluator_8h" name="SimRateEvaluator.h" local="yes" imported="no">SimRateEvaluator.h</includes>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>Line.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Line_8cpp</filename>
    <includes id="Line_8h" name="Line.h" local="yes" imported="no">Line.h</includes>
  </compound>
  <compound kind="file">
    <name>Line.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Line_8h</filename>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="HyperPlane_8h" name="HyperPlane.h" local="yes" imported="no">HyperPlane.h</includes>
  </compound>
  <compound kind="file">
    <name>ListNode.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ListNode_8h</filename>
  </compound>
  <compound kind="file">
    <name>LookupConsHdlr.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>LookupConsHdlr_8cpp</filename>
    <includes id="LookupConsHdlr_8h" name="LookupConsHdlr.h" local="yes" imported="no">LookupConsHdlr.h</includes>
    <member kind="enumeration">
      <type></type>
      <name>Side</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a8c0137d7160ad71b6ed265c53c99ed00</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>checkCons</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a3b33301677a9cf8f19abf7d0e949bc5e</anchor>
      <arglist>(SCIP *scip, SCIP_CONS *cons, SCIP_SOL *sol, bool *violated)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>determinant</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>adaa567b91b4c6f9260e6409f54eeeb60</anchor>
      <arglist>(std::pair&lt; double, double &gt; &amp;A, std::pair&lt; double, double &gt; &amp;B, std::pair&lt; double, double &gt; &amp;C)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grahamScanCheck</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>aaa86610522d9939aad27109785c11e58</anchor>
      <arglist>(std::vector&lt; std::pair&lt; double, double &gt; &gt; &amp;convexHull)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>computeConvexHull</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a6b9422f39be86955465d9d281f388062</anchor>
      <arglist>(SCIP *scip, SCIP_CONSDATA *consdata, std::vector&lt; std::pair&lt; double, double &gt; &gt; &amp;out)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>separateCons</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>ac27d86ef99e02923b54fa7474e061ade</anchor>
      <arglist>(SCIP *scip, SCIP_CONS *cons, SCIP_SOL *sol, bool *success)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>propagateCons</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a3a18d0211cb79aff9242a6687e6ffaf1</anchor>
      <arglist>(SCIP *scip, SCIP_CONS *cons, SCIP_RESULT *result)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_EVENTEXEC</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a7f0257d53942e0ed8216ec5c96cf5e9c</anchor>
      <arglist>(LookupConsHdlr::scip_exec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSDELETE</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>af3b783c8234b404c82fe93839fd788d0</anchor>
      <arglist>(LookupConsHdlr::scip_delete)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSTRANS</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a92e4c47365596e5f79d11da08f137fae</anchor>
      <arglist>(LookupConsHdlr::scip_trans)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSSEPALP</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a843700b1869f6e6ab91311d3d06bb9b5</anchor>
      <arglist>(LookupConsHdlr::scip_sepalp)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>solutionIsExcluded</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a07960e9cf8a0555829b506b352b44861</anchor>
      <arglist>(SCIP *scip, SCIP_SOL *sol, SCIP_CONS *cons)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSSEPASOL</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a9452127bc947777551fa3644fd108071</anchor>
      <arglist>(LookupConsHdlr::scip_sepasol)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSENFOLP</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>ac24911ff8602691b70b555f6a9c590e1</anchor>
      <arglist>(LookupConsHdlr::scip_enfolp)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSENFOPS</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a319b0d16f54027e6167f5f239d0f8bf0</anchor>
      <arglist>(LookupConsHdlr::scip_enfops)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSCHECK</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a6d80c2ed42f3ed5cc5a8b8993b6e09ea</anchor>
      <arglist>(LookupConsHdlr::scip_check)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSPROP</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>af22df366c44678dfb3ace54c3aa5cb72</anchor>
      <arglist>(LookupConsHdlr::scip_prop)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSLOCK</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a47db5e446a45c379e648dc109c3890bb</anchor>
      <arglist>(LookupConsHdlr::scip_lock)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSDELVARS</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>aa7edc4fe8c09763cef2cefdd3e8dbfd2</anchor>
      <arglist>(LookupConsHdlr::scip_delvars)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSPRINT</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>adbe88ba5cb0974305ad500506b0dcc4f</anchor>
      <arglist>(LookupConsHdlr::scip_print)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSHDLRCLONE</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a19acbcf3c4b1aad03bddb334f79a04a9</anchor>
      <arglist>(scip::ObjProbCloneable *LookupConsHdlr::clone)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_CONSCOPY</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>adaa85106e9ced97e1015cf7a888f3b92</anchor>
      <arglist>(LookupConsHdlr::scip_copy)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPcreateConsLookup</name>
      <anchorfile>LookupConsHdlr_8cpp.shtml</anchorfile>
      <anchor>a44ee93408d5610778c80a229dfa977b0</anchor>
      <arglist>(SCIP *scip, SCIP_CONS **cons, const char *name, SCIP_VAR *forwardVar, SCIP_VAR *arg, const boost::shared_ptr&lt; spline::PiecewiseLinear &gt; &amp;linearModel, const boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 3 &gt; &gt; &amp;lookup, const boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 2 &gt; &gt; &amp;deriv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>LookupConsHdlr.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>LookupConsHdlr_8h</filename>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPcreateConsLookup</name>
      <anchorfile>LookupConsHdlr_8h.shtml</anchorfile>
      <anchor>a44ee93408d5610778c80a229dfa977b0</anchor>
      <arglist>(SCIP *scip, SCIP_CONS **cons, const char *name, SCIP_VAR *forwardVar, SCIP_VAR *arg, const boost::shared_ptr&lt; spline::PiecewiseLinear &gt; &amp;linearModel, const boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 3 &gt; &gt; &amp;lookup, const boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 2 &gt; &gt; &amp;deriv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MdlExpressionTranslator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>MdlExpressionTranslator_8cpp</filename>
    <includes id="MdlExpressionTranslator_8h" name="MdlExpressionTranslator.h" local="yes" imported="no">MdlExpressionTranslator.h</includes>
    <includes id="ExprLookup_8h" name="ExprLookup.h" local="yes" imported="no">ExprLookup.h</includes>
    <includes id="ExprPiecewiseLinear_8h" name="ExprPiecewiseLinear.h" local="yes" imported="no">ExprPiecewiseLinear.h</includes>
  </compound>
  <compound kind="file">
    <name>MdlExpressionTranslator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>MdlExpressionTranslator_8h</filename>
    <member kind="typedef">
      <type>boost::shared_ptr&lt; spline::BSplineCurve&lt; 3, SCIP_Real &gt; &gt;</type>
      <name>SplinePtr</name>
      <anchorfile>MdlExpressionTranslator_8h.shtml</anchorfile>
      <anchor>adb6f33b68d84680d871f5f4681dc05d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::unordered_map&lt; sdo::ExpressionGraph::Node *, SplinePtr &gt;</type>
      <name>LookupMap</name>
      <anchorfile>MdlExpressionTranslator_8h.shtml</anchorfile>
      <anchor>ae6925f68225b3c0a1be669e2d260add6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>NLPGraph.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>NLPGraph_8cpp</filename>
    <includes id="NLPGraph_8h" name="NLPGraph.h" local="yes" imported="no">NLPGraph.h</includes>
  </compound>
  <compound kind="file">
    <name>NLPGraph.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>NLPGraph_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>ODEintegrator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ODEintegrator_8cpp</filename>
    <includes id="ODEintegrator_8h" name="ODEintegrator.h" local="yes" imported="no">ODEintegrator.h</includes>
  </compound>
  <compound kind="file">
    <name>ODEintegrator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ODEintegrator_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="ConstRateEvaluator_8h" name="ConstRateEvaluator.h" local="yes" imported="no">ConstRateEvaluator.h</includes>
    <includes id="SimRateEvaluator_8h" name="SimRateEvaluator.h" local="yes" imported="no">SimRateEvaluator.h</includes>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>Orthant.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Orthant_8cpp</filename>
    <includes id="Orthant_8h" name="Orthant.h" local="yes" imported="no">Orthant.h</includes>
  </compound>
  <compound kind="file">
    <name>Orthant.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Orthant_8h</filename>
  </compound>
  <compound kind="file">
    <name>OrthantList.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>OrthantList_8cpp</filename>
    <includes id="OrthantList_8h" name="OrthantList.h" local="yes" imported="no">OrthantList.h</includes>
  </compound>
  <compound kind="file">
    <name>OrthantList.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>OrthantList_8h</filename>
    <includes id="Orthant_8h" name="Orthant.h" local="yes" imported="no">Orthant.h</includes>
  </compound>
  <compound kind="file">
    <name>Point.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Point_8cpp</filename>
    <includes id="Point_8h" name="Point.h" local="yes" imported="no">Point.h</includes>
  </compound>
  <compound kind="file">
    <name>Point.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Point_8h</filename>
  </compound>
  <compound kind="file">
    <name>PointODEintegrator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PointODEintegrator_8cpp</filename>
    <includes id="PointODEintegrator_8h" name="PointODEintegrator.h" local="yes" imported="no">PointODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>PointODEintegrator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PointODEintegrator_8h</filename>
    <includes id="ODEintegrator_8h" name="ODEintegrator.h" local="yes" imported="no">ODEintegrator.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="ConstRateEvaluator_8h" name="ConstRateEvaluator.h" local="yes" imported="no">ConstRateEvaluator.h</includes>
    <includes id="SimRateEvaluator_8h" name="SimRateEvaluator.h" local="yes" imported="no">SimRateEvaluator.h</includes>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <includes id="CopyablePointer_8h" name="CopyablePointer.h" local="yes" imported="no">CopyablePointer.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>PointRateEvaluator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PointRateEvaluator_8cpp</filename>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>PointRateEvaluator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PointRateEvaluator_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
  </compound>
  <compound kind="file">
    <name>PresolConsGraph.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PresolConsGraph_8cpp</filename>
    <includes id="PresolConsGraph_8h" name="PresolConsGraph.h" local="yes" imported="no">PresolConsGraph.h</includes>
    <includes id="NLPGraph_8h" name="NLPGraph.h" local="yes" imported="no">NLPGraph.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PRESOLEXEC</name>
      <anchorfile>PresolConsGraph_8cpp.shtml</anchorfile>
      <anchor>a470c7fd868f595d77aad465ddd065548</anchor>
      <arglist>(PresolConsGraph::scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PresolConsGraph.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PresolConsGraph_8h</filename>
  </compound>
  <compound kind="file">
    <name>PresolCppMin.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PresolCppMin_8cpp</filename>
    <includes id="PresolCppMin_8h" name="PresolCppMin.h" local="yes" imported="no">PresolCppMin.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>PRESOL_NAME</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>a285550aa0594c4c2826a42f769de63cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PRESOL_DESC</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>afb9e88e58ce104f4d248c85983b37a2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PRESOL_PRIORITY</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>a843930ba9a9b28a2392957fe9f554aa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PRESOL_MAXROUNDS</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>ae2d39da34a44d64d7854b43b08434108</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PRESOL_DELAY</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>a897c2ad2a660e966992d98344041f5cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PRESOLEXEC</name>
      <anchorfile>PresolCppMin_8cpp.shtml</anchorfile>
      <anchor>aa31a4871ec8523033b4de50bacce2609</anchor>
      <arglist>(PresolCppMin::scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PresolCppMin.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PresolCppMin_8h</filename>
  </compound>
  <compound kind="file">
    <name>ProbDataCtrl.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ProbDataCtrl_8cpp</filename>
    <includes id="ProbDataCtrl_8h" name="ProbDataCtrl.h" local="yes" imported="no">ProbDataCtrl.h</includes>
  </compound>
  <compound kind="file">
    <name>ProbDataCtrl.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ProbDataCtrl_8h</filename>
  </compound>
  <compound kind="file">
    <name>ProbDataSD.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ProbDataSD_8cpp</filename>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DIALOG_NAME</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a2a46040cdecc68ce461a7f1b9750bad7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DIALOG_WRITE_NAME</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ac7d8d45029446504ec6c6017eb4631f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DIALOG_DESC</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a0c5621b7189a21c3a70322a74cb87a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DIALOG_ISSUBMENU</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>aa4f5ad4ee2a0a6b1dd180a64381a0dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDinit</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a51b513f01ab626df4153d95759083f50</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDensureValidStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a9979cad67cad65ddeefaefdfb656cde2</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDrefreshStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a96bbcd98e886d686b9a2dadb672f06db</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>checkStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a6a2f75720add8e081f0489d94e8eeea9</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStructureSummary</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>affa2620c16180bce2a6cbf00b537ae8b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDreadStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>aadf047ab7385c9ffe93c80de5576355f</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDcheckStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a377f755739a17c4fc880f367aba55052</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ac062c7df31597f3a0e00dd272205ad1c</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDaddConsWithVars</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a86a59d74950f87d84e7fdf5586da0cb6</anchor>
      <arglist>(SCIP_CONS *currentCons, SCIP *scip, SCIP *subscip, SCIP_HASHMAP *varmap, SCIP_HASHMAP *consmap, SCIP_Bool noObj, SCIP_Bool global, std::map&lt; SCIP_VAR *, SCIP_Real &gt; *solMap, SCIP_Bool copysol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SDsetIsReformulated</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>af8b355e4dcc3eb0e6ed55ddfac53fda2</anchor>
      <arglist>(SCIP *scip, bool isReformulated)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDgetIsReformulated</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ad3d56b387ae409f9c053e76ad04d524b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SDsetIsStructureValid</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ae4f72cc0d5f3b5c0dc54287d37d62c46</anchor>
      <arglist>(SCIP *scip, bool isValid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDgetIsStructureValid</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ad2beeb5b25c5beb82bc8aa9b6d1422d8</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStateVarNames</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>acc3a19616ab4187e17cae3ca394d3d3d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDfixVarProbingExact</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>adcf1aacc0fa8adc8c8d197777810e68f</anchor>
      <arglist>(SCIP *scip, SCIP_VAR *var, SCIP_Real fixVal)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDinit</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a1373a666370e32a8aa14821b46981b13</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDprintStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>abaab5f09125b15e11a40a0faae0df684</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDensureValidStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a45913a25549a7cd80d36223ee7c6e696</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDrefreshStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ac0b508f6f580db4b298ad2eab273b4e1</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDdoSomething</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a3f8803d067f11f7d47d85001b6fc49b9</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDdisable</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>adbc9b47a8ef1d60082a61ceca001e05f</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>sdscip::SDproblemStructureInterface *</type>
      <name>SDgetStructure</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a42f19d036c6657e05de372b142071e8d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogWriteTransprobSD</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a5b37a6bef27999b05393c18dc1b302c1</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPaddParamsSD</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>a65018ddee342e09c5c0a5f0818f62c82</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDisEquation</name>
      <anchorfile>ProbDataSD_8cpp.shtml</anchorfile>
      <anchor>ac11158f2c4aa30f7eb198a52cff22abe</anchor>
      <arglist>(SCIP *scip, SCIP_CONS *cons)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ProbDataSD.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ProbDataSD_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="SDproblemStructureFactory_8h" name="SDproblemStructureFactory.h" local="yes" imported="no">SDproblemStructureFactory.h</includes>
    <includes id="pub__message__sd_8h" name="pub_message_sd.h" local="yes" imported="no">pub_message_sd.h</includes>
    <member kind="typedef">
      <type>std::vector&lt; SCIP_VAR * &gt;</type>
      <name>VarVec</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a9b0c945c2166e603da9787cab67f55f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, unsigned int &gt;</type>
      <name>IntIntMap</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ae287373c6c544ddf5077173c1bc1631e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SCIP_CONS *, SCIP_VAR * &gt;</type>
      <name>ConsVarPair</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a48d1d37768b4e450006e2ffafae12798</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; ConsVarPair &gt;</type>
      <name>ConsVarVec</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a1586aca42ad783096ce0d5955923ff51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, std::vector&lt; SCIP_CONS * &gt; &gt;</type>
      <name>PropCutMap</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a927d26a23b2827fbd05bac579fd8ccb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDrefreshStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a96bbcd98e886d686b9a2dadb672f06db</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDensureValidStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a9979cad67cad65ddeefaefdfb656cde2</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDreadStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>aadf047ab7385c9ffe93c80de5576355f</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDcheckStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a377f755739a17c4fc880f367aba55052</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStructureSummary</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>affa2620c16180bce2a6cbf00b537ae8b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ac062c7df31597f3a0e00dd272205ad1c</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDprintStateVarNames</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>acc3a19616ab4187e17cae3ca394d3d3d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>sdscip::SDproblemStructureInterface *</type>
      <name>SDgetStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a42f19d036c6657e05de372b142071e8d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDaddConsWithVars</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a86a59d74950f87d84e7fdf5586da0cb6</anchor>
      <arglist>(SCIP_CONS *currentCons, SCIP *scip, SCIP *subscip, SCIP_HASHMAP *varmap, SCIP_HASHMAP *consmap, SCIP_Bool noObj, SCIP_Bool global, std::map&lt; SCIP_VAR *, SCIP_Real &gt; *solMap, SCIP_Bool copysol)</arglist>
    </member>
    <member kind="function">
      <type>PropCutMap *</type>
      <name>SDgetPropCuts</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ae13e1b37a5cb1c24242da83d93045468</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SDsetIsReformulated</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>af8b355e4dcc3eb0e6ed55ddfac53fda2</anchor>
      <arglist>(SCIP *scip, bool isReformulated)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDgetIsReformulated</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ad3d56b387ae409f9c053e76ad04d524b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SDsetIsStructureValid</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ae4f72cc0d5f3b5c0dc54287d37d62c46</anchor>
      <arglist>(SCIP *scip, bool isValid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDgetIsStructureValid</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ad2beeb5b25c5beb82bc8aa9b6d1422d8</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SDisEquation</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ac11158f2c4aa30f7eb198a52cff22abe</anchor>
      <arglist>(SCIP *scip, SCIP_CONS *cons)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>SDgetVarBasename</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a8d105685fd0c9ab886ef3ba4d759e93e</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDfixVarProbingExact</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>adcf1aacc0fa8adc8c8d197777810e68f</anchor>
      <arglist>(SCIP *scip, SCIP_VAR *var, SCIP_Real fixVal)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDinit</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a1373a666370e32a8aa14821b46981b13</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDprintStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>abaab5f09125b15e11a40a0faae0df684</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDensureValidStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a45913a25549a7cd80d36223ee7c6e696</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogWriteTransprobSD</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a5b37a6bef27999b05393c18dc1b302c1</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDrefreshStructure</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>ac0b508f6f580db4b298ad2eab273b4e1</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDdoSomething</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a3f8803d067f11f7d47d85001b6fc49b9</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeDialogSDdisable</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>adbc9b47a8ef1d60082a61ceca001e05f</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPaddParamsSD</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a65018ddee342e09c5c0a5f0818f62c82</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SDinit</name>
      <anchorfile>ProbDataSD_8h.shtml</anchorfile>
      <anchor>a51b513f01ab626df4153d95759083f50</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>prop_obobt.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>prop__obobt_8cpp</filename>
    <includes id="prop__obobt_8h" name="prop_obobt.h" local="yes" imported="no">prop_obobt.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>PROP_NAME</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a2062ba7b5292b2cb9456209022cbdac7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PROP_DESC</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a01f6c19c723e33bb044d0e466828ac80</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PROP_TIMING</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a95706b8e33186c2eea7c0bc857974b46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PROP_PRIORITY</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>af54d22d68dc88e0702c6387381260bdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PROP_FREQ</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>aef556cb12e7377f21103a6ffe5764c30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PROP_DELAY</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a7004d49c05d1b2473ff254d4c4d575fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_CREATE_GENVBOUNDS</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>aa32bcaf31a481d97e0b2870431857bd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_FILTERING_NORM</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a75006f93f83093efaa68ef56ff318886</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_APPLY_FILTERROUNDS</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a18d920166fc99a8159e87a9111ed3b05</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_DUALFEASTOL</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a201186ee6233f7ff8223046d095b21a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_CONDITIONLIMIT</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a4c2f55d95fdf7b580fc1d3b126cfe01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_FILTERING_MIN</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a28ec81eb824909233c59db28b78fcf8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_ITLIMITFACTOR</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a5fa4e559bb4084a647c0dacf2d15c6b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_MAXLOOKAHEAD</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a76c05e235e31df9dc43dc3ab357ff38d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OBBT_SCOREBASE</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a68f9721e1d699a6f20df8a7d84f816ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GENVBOUND_PROP_NAME</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a0e9771028bca3552886efe58d1011d7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct Bound</type>
      <name>BOUND</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a249bb964a2963b5e1c8f08e889d743d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct BoundGroup</type>
      <name>BOUNDGROUP</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>ac6cdb22b0c51358b99ba851fa33b6b50</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludePropObobt</name>
      <anchorfile>prop__obobt_8cpp.shtml</anchorfile>
      <anchor>a712e2e59147c5b0254f74b4f307980be</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>prop_obobt.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>prop__obobt_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludePropObobt</name>
      <anchorfile>prop__obobt_8h.shtml</anchorfile>
      <anchor>a712e2e59147c5b0254f74b4f307980be</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropagationPattern.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropagationPattern_8cpp</filename>
    <includes id="PropagationPattern_8h" name="PropagationPattern.h" local="yes" imported="no">PropagationPattern.h</includes>
    <includes id="HyperCube_8h" name="HyperCube.h" local="yes" imported="no">HyperCube.h</includes>
  </compound>
  <compound kind="file">
    <name>PropagationPattern.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropagationPattern_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="HyperCube_8h" name="HyperCube.h" local="yes" imported="no">HyperCube.h</includes>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>ObjectiveValuesVec</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a93d1899ccfc3d7bebf357011afc15290</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SCIP_VAR *, SCIP_VAR * &gt;</type>
      <name>VarPair</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a6c255a2244bbb4263b14a4cd88dd32d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VarPair &gt;</type>
      <name>VarPairVec</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a25d79470b0dbca9d48353057ecddf727</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; ObjectiveValuesVec &gt;</type>
      <name>PatternVec</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>ac827e9e760dee8abb95a013b3008fd8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum SDSCIP_PropDir</type>
      <name>SDSCIP_PROPDIR</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>abaca251905b1d08379a19f9f473a8069</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SDSCIP_PropDir</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a7aeb24568d9830c4d31631be769d46da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SDSCIP_UP</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a7aeb24568d9830c4d31631be769d46daaec79c062c72887fc9ed597f4ac75edd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SDSCIP_DOWN</name>
      <anchorfile>PropagationPattern_8h.shtml</anchorfile>
      <anchor>a7aeb24568d9830c4d31631be769d46daad9fb82298776f62504837e5a49e072c0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropCtrlOBBT.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropCtrlOBBT_8cpp</filename>
    <includes id="PropCtrlOBBT_8h" name="PropCtrlOBBT.h" local="yes" imported="no">PropCtrlOBBT.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>PropCtrlOBBT_8cpp.shtml</anchorfile>
      <anchor>a7ac9aa2eac91e9fece2e498b3045956d</anchor>
      <arglist>(PropCtrlOBBT::scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropCtrlOBBT.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropCtrlOBBT_8h</filename>
  </compound>
  <compound kind="file">
    <name>PropOBRA.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropOBRA_8cpp</filename>
    <includes id="PropOBRA_8h" name="PropOBRA.h" local="yes" imported="no">PropOBRA.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>HASHTABLESIZE_FACTOR</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>a512d38a9f09ec24fb73afe49285af4dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; B, A &gt;</type>
      <name>flip_pair</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>aef29cdc55d3b6ec31d2644b59a803886</anchor>
      <arglist>(const std::pair&lt; A, B &gt; &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>std::multimap&lt; B, A &gt;</type>
      <name>flip_map</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>a2d4f7b90688a003ae4d8202fe879cd7e</anchor>
      <arglist>(const std::map&lt; A, B &gt; &amp;src)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>readSubscipParams</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>ab445c49baf8484efdb2870438cd9225f</anchor>
      <arglist>(SCIP *scip, SCIP *subscip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPINIT</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>a9cf9f232fb7438e34a323b8438ee0166</anchor>
      <arglist>(PropOBRA::scip_init)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>a8eda1624f4ae1c65f554a8b03b79c25b</anchor>
      <arglist>(PropOBRA::scip_exec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPPRESOL</name>
      <anchorfile>PropOBRA_8cpp.shtml</anchorfile>
      <anchor>ac6493f32f338d6ec020687c37e9f9650</anchor>
      <arglist>(PropOBRA::scip_presol)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropOBRA.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropOBRA_8h</filename>
    <includes id="PropagationPattern_8h" name="PropagationPattern.h" local="yes" imported="no">PropagationPattern.h</includes>
  </compound>
  <compound kind="file">
    <name>PropODE.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropODE_8cpp</filename>
    <includes id="PropODE_8h" name="PropODE.h" local="yes" imported="no">PropODE.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPINIT</name>
      <anchorfile>PropODE_8cpp.shtml</anchorfile>
      <anchor>ae26ac04710490baa7eb79a82d1be8bf8</anchor>
      <arglist>(PropODE::scip_init)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>PropODE_8cpp.shtml</anchorfile>
      <anchor>ace735066e787a87b546948809f36b881</anchor>
      <arglist>(PropODE::scip_exec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPPRESOL</name>
      <anchorfile>PropODE_8cpp.shtml</anchorfile>
      <anchor>af87ce802ce80b43b1286a7cb72b40387</anchor>
      <arglist>(PropODE::scip_presol)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropODE.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropODE_8h</filename>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="IntervalODEintegrator_8h" name="IntervalODEintegrator.h" local="yes" imported="no">IntervalODEintegrator.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="Statistics_8h" name="Statistics.h" local="yes" imported="no">Statistics.h</includes>
  </compound>
  <compound kind="file">
    <name>PropProbingObjTest.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropProbingObjTest_8cpp</filename>
    <includes id="PropProbingObjTest_8h" name="PropProbingObjTest.h" local="yes" imported="no">PropProbingObjTest.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>PropProbingObjTest_8cpp.shtml</anchorfile>
      <anchor>acf87730fd2aec074cf98fb8762726846</anchor>
      <arglist>(PropProbingObjTest::scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PropProbingObjTest.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>PropProbingObjTest_8h</filename>
  </compound>
  <compound kind="file">
    <name>pub_message_sd.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>pub__message__sd_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SCIPdbgMsg</name>
      <anchorfile>pub__message__sd_8h.shtml</anchorfile>
      <anchor>ab9faf79539c4d2cfe2a476e8b2190328</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCIPcppDbgMsg</name>
      <anchorfile>pub__message__sd_8h.shtml</anchorfile>
      <anchor>accb3b34c846d5d751dd6dcb73d6b1ad0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCIPdbg</name>
      <anchorfile>pub__message__sd_8h.shtml</anchorfile>
      <anchor>ad89f3cda17548a9b16fbe7b6474b74fe</anchor>
      <arglist>(x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reader_osilc.c</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>reader__osilc_8c</filename>
    <includes id="reader__osilc_8h" name="reader_osilc.h" local="yes" imported="no">reader_osilc.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>READER_NAME</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>ab96209313aa41036fa78dccf3a65ddbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>READER_DESC</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>a6af7670d26c84862991598647730b552</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>READER_EXTENSION</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>a8c484111d1fbef7ebfeeb82b850de9f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>M_PI</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>ae71449b1cc6e6250b91f539153a7a0d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>M_E</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>a9bf5d952c5c93c70f9e66c9794d406c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CONSTYPE</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>aaf05d630a91fd6a3bcc1a2587bc72af8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>LINEAR</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>aaf05d630a91fd6a3bcc1a2587bc72af8adc101ebf31c49c2d4b80b7c6f59f22cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>QUADRATIC</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>aaf05d630a91fd6a3bcc1a2587bc72af8a2e8d8a1445172e2e64293e1dd0558b0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>NONLINEAR</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>aaf05d630a91fd6a3bcc1a2587bc72af8a0b885a5372ee4ad1444b8f72f8187b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeReaderOsilC</name>
      <anchorfile>reader__osilc_8c.shtml</anchorfile>
      <anchor>a8792c79bd710af6b8e506585cc49b54c</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reader_osilc.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>reader__osilc_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>SCIPincludeReaderOsilC</name>
      <anchorfile>reader__osilc_8h.shtml</anchorfile>
      <anchor>a8792c79bd710af6b8e506585cc49b54c</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ReaderVOP.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ReaderVOP_8cpp</filename>
    <includes id="ReaderVOP_8h" name="ReaderVOP.h" local="yes" imported="no">ReaderVOP.h</includes>
    <includes id="SDList_8h" name="SDList.h" local="yes" imported="no">SDList.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="MdlExpressionTranslator_8h" name="MdlExpressionTranslator.h" local="yes" imported="no">MdlExpressionTranslator.h</includes>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_READERFREE</name>
      <anchorfile>ReaderVOP_8cpp.shtml</anchorfile>
      <anchor>ac79f1de1a4b431f536406b268670d7af</anchor>
      <arglist>(sdo::ReaderVOP::scip_free)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_READERREAD</name>
      <anchorfile>ReaderVOP_8cpp.shtml</anchorfile>
      <anchor>a7fded2f3544f929763e2028a525066cc</anchor>
      <arglist>(sdo::ReaderVOP::scip_read)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SCIP_DECL_READERWRITE</name>
      <anchorfile>ReaderVOP_8cpp.shtml</anchorfile>
      <anchor>a25abcc099fbf0e3fa4ea251bc469a5c8</anchor>
      <arglist>(sdo::ReaderVOP::scip_write)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ReaderVOP.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ReaderVOP_8h</filename>
  </compound>
  <compound kind="file">
    <name>ReduceODEintegrator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ReduceODEintegrator_8cpp</filename>
    <includes id="ReduceODEintegrator_8hpp" name="ReduceODEintegrator.hpp" local="yes" imported="no">ReduceODEintegrator.hpp</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>ReduceODEintegrator.hpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>ReduceODEintegrator_8hpp</filename>
    <includes id="ODEintegrator_8h" name="ODEintegrator.h" local="yes" imported="no">ODEintegrator.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PointODEintegrator_8h" name="PointODEintegrator.h" local="yes" imported="no">PointODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="ConstRateEvaluator_8h" name="ConstRateEvaluator.h" local="yes" imported="no">ConstRateEvaluator.h</includes>
    <includes id="SimRateEvaluator_8h" name="SimRateEvaluator.h" local="yes" imported="no">SimRateEvaluator.h</includes>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
  </compound>
  <compound kind="file">
    <name>SBrateEvaluator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SBrateEvaluator_8cpp</filename>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <member kind="function">
      <type></type>
      <name>if</name>
      <anchorfile>SBrateEvaluator_8cpp.shtml</anchorfile>
      <anchor>a7b716a76428d14b0fb2358d4e04fa17b</anchor>
      <arglist>(globalEnclosureLbs_.find(n)!=globalEnclosureLbs_.end())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>if</name>
      <anchorfile>SBrateEvaluator_8cpp.shtml</anchorfile>
      <anchor>ab6921e1305492564b828e5a445d5d5d7</anchor>
      <arglist>(useVarBounds)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>if</name>
      <anchorfile>SBrateEvaluator_8cpp.shtml</anchorfile>
      <anchor>af4dd96c817a7997921bab0b8d145b5e7</anchor>
      <arglist>(candidates.size() &gt;=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>if</name>
      <anchorfile>SBrateEvaluator_8cpp.shtml</anchorfile>
      <anchor>acdf18a4224c2ddefe645a1fdcec15a50</anchor>
      <arglist>(globalEnclosureUbs_.find(n)!=globalEnclosureUbs_.end())</arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>n</name>
      <anchorfile>SBrateEvaluator_8cpp.shtml</anchorfile>
      <anchor>aeab71244afb687f16d8c4f5ee9d6ef0e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SBrateEvaluator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SBrateEvaluator_8h</filename>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
  </compound>
  <compound kind="file">
    <name>SDCons.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDCons_8cpp</filename>
    <includes id="SDCons_8h" name="SDCons.h" local="yes" imported="no">SDCons.h</includes>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>CreateMinMaxCons</name>
      <anchorfile>SDCons_8cpp.shtml</anchorfile>
      <anchor>a34bc2d8ebfb624222687be8f57eff8cc</anchor>
      <arglist>(SCIP *scip, SDCons *sdcons, SDConsType type, SCIP_VAR *forward_var, SCIP_VAR *arg0, SCIP_VAR *arg1)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SDCons.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDCons_8h</filename>
    <member kind="enumeration">
      <type></type>
      <name>SDConsType</name>
      <anchorfile>SDCons_8h.shtml</anchorfile>
      <anchor>a04e28832e9e59cbfb62bc92dc89437b9</anchor>
      <arglist></arglist>
      <enumvalue file="SDCons_8h.shtml" anchor="a04e28832e9e59cbfb62bc92dc89437b9ae5564829e2f85f6a6873a9d5c4f26d09">SIMPLE</enumvalue>
      <enumvalue file="SDCons_8h.shtml" anchor="a04e28832e9e59cbfb62bc92dc89437b9ace31e2a082d17e038fcc6e3006166653">MIN</enumvalue>
      <enumvalue file="SDCons_8h.shtml" anchor="a04e28832e9e59cbfb62bc92dc89437b9a26a4b44a837bf97b972628509912b4a5">MAX</enumvalue>
      <enumvalue file="SDCons_8h.shtml" anchor="a04e28832e9e59cbfb62bc92dc89437b9a9498418a6b5da2511af7463648698201">CONST_MIN</enumvalue>
      <enumvalue file="SDCons_8h.shtml" anchor="a04e28832e9e59cbfb62bc92dc89437b9a85e795dc24b8a451b615166a295fdbca">CONST_MAX</enumvalue>
    </member>
  </compound>
  <compound kind="file">
    <name>SDControl.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDControl_8h</filename>
    <includes id="ListNode_8h" name="ListNode.h" local="yes" imported="no">ListNode.h</includes>
  </compound>
  <compound kind="file">
    <name>SDList.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDList_8h</filename>
    <includes id="SDVariable_8h" name="SDVariable.h" local="yes" imported="no">SDVariable.h</includes>
    <includes id="SDListBuilder_8h" name="SDListBuilder.h" local="yes" imported="no">SDListBuilder.h</includes>
  </compound>
  <compound kind="file">
    <name>SDListBuilder.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDListBuilder_8h</filename>
    <includes id="SDListTraits_8h" name="SDListTraits.h" local="yes" imported="no">SDListTraits.h</includes>
  </compound>
  <compound kind="file">
    <name>SDListTraits.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDListTraits_8h</filename>
    <includes id="SDVariable_8h" name="SDVariable.h" local="yes" imported="no">SDVariable.h</includes>
    <includes id="SDControl_8h" name="SDControl.h" local="yes" imported="no">SDControl.h</includes>
    <member kind="typedef">
      <type>typename SDListTraits&lt; T, VAR_ID &gt;::key_t</type>
      <name>key_type</name>
      <anchorfile>SDListTraits_8h.shtml</anchorfile>
      <anchor>ac919f9e186dd885858c99bbb6ef9f0f9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SDproblemStructure.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructure_8cpp</filename>
    <includes id="SDproblemStructure_8h" name="SDproblemStructure.h" local="yes" imported="no">SDproblemStructure.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructure.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructure_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureExtendedInterface.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureExtendedInterface_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureFactory.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureFactory_8cpp</filename>
    <includes id="SDproblemStructureFactory_8h" name="SDproblemStructureFactory.h" local="yes" imported="no">SDproblemStructureFactory.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureFactory.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureFactory_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="SDproblemStructure_8h" name="SDproblemStructure.h" local="yes" imported="no">SDproblemStructure.h</includes>
    <includes id="SDproblemStructureV1_8h" name="SDproblemStructureV1.h" local="yes" imported="no">SDproblemStructureV1.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureInterface.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureInterface_8cpp</filename>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureInterface.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureInterface_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureV1.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureV1_8cpp</filename>
    <includes id="SDproblemStructureV1_8h" name="SDproblemStructureV1.h" local="yes" imported="no">SDproblemStructureV1.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
  </compound>
  <compound kind="file">
    <name>SDproblemStructureV1.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDproblemStructureV1_8h</filename>
    <includes id="SDList_8h" name="SDList.h" local="yes" imported="no">SDList.h</includes>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
  </compound>
  <compound kind="file">
    <name>sdscip.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>sdscip_8h</filename>
    <includes id="pub__message__sd_8h" name="pub_message_sd.h" local="yes" imported="no">pub_message_sd.h</includes>
  </compound>
  <compound kind="file">
    <name>SDSCIPtest.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDSCIPtest_8cpp</filename>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>SDSCIPtest.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDSCIPtest_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="BaseTest_8h" name="BaseTest.h" local="yes" imported="no">BaseTest.h</includes>
  </compound>
  <compound kind="file">
    <name>SDVarBasic.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDVarBasic_8cpp</filename>
    <includes id="SDVarBasic_8h" name="SDVarBasic.h" local="yes" imported="no">SDVarBasic.h</includes>
  </compound>
  <compound kind="file">
    <name>SDVarBasic.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDVarBasic_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
  </compound>
  <compound kind="file">
    <name>SDVariable.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SDVariable_8h</filename>
    <includes id="ListNode_8h" name="ListNode.h" local="yes" imported="no">ListNode.h</includes>
    <includes id="SDCons_8h" name="SDCons.h" local="yes" imported="no">SDCons.h</includes>
  </compound>
  <compound kind="file">
    <name>SimRateEvaluator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SimRateEvaluator_8cpp</filename>
    <includes id="SimRateEvaluator_8h" name="SimRateEvaluator.h" local="yes" imported="no">SimRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>SimRateEvaluator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>SimRateEvaluator_8h</filename>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
  </compound>
  <compound kind="file">
    <name>Statistics.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Statistics_8cpp</filename>
    <includes id="Statistics_8h" name="Statistics.h" local="yes" imported="no">Statistics.h</includes>
  </compound>
  <compound kind="file">
    <name>Statistics.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Statistics_8h</filename>
  </compound>
  <compound kind="file">
    <name>TestBoundMap.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestBoundMap_8cpp</filename>
    <includes id="TestBoundMap_8h" name="TestBoundMap.h" local="yes" imported="no">TestBoundMap.h</includes>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a1d12301bdd4ec036a5d18a71a80913dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a912bc46871c3a24d837e9933224a466c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TestBoundMap.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestBoundMap_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SDproblemStructureInterface_8h" name="SDproblemStructureInterface.h" local="yes" imported="no">SDproblemStructureInterface.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>TestEstimatorTypes.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestEstimatorTypes_8cpp</filename>
    <includes id="TestEstimatorTypes_8h" name="TestEstimatorTypes.h" local="yes" imported="no">TestEstimatorTypes.h</includes>
  </compound>
  <compound kind="file">
    <name>TestEstimatorTypes.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestEstimatorTypes_8h</filename>
    <includes id="TestExprPiecewiseLinear_8h" name="TestExprPiecewiseLinear.h" local="yes" imported="no">TestExprPiecewiseLinear.h</includes>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="ExprPiecewiseLinear_8h" name="ExprPiecewiseLinear.h" local="yes" imported="no">ExprPiecewiseLinear.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
    <includes id="TestSDplugin_8h" name="TestSDplugin.h" local="yes" imported="no">TestSDplugin.h</includes>
  </compound>
  <compound kind="file">
    <name>TestExprPiecewiseLinear.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestExprPiecewiseLinear_8cpp</filename>
    <includes id="TestExprPiecewiseLinear_8h" name="TestExprPiecewiseLinear.h" local="yes" imported="no">TestExprPiecewiseLinear.h</includes>
  </compound>
  <compound kind="file">
    <name>TestExprPiecewiseLinear.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestExprPiecewiseLinear_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="ExprPiecewiseLinear_8h" name="ExprPiecewiseLinear.h" local="yes" imported="no">ExprPiecewiseLinear.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="BoundMapHelpers_8cpp" name="BoundMapHelpers.cpp" local="yes" imported="no">BoundMapHelpers.cpp</includes>
    <includes id="TestSDplugin_8h" name="TestSDplugin.h" local="yes" imported="no">TestSDplugin.h</includes>
  </compound>
  <compound kind="file">
    <name>TestGeom.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestGeom_8cpp</filename>
    <includes id="TestGeom_8h" name="TestGeom.h" local="yes" imported="no">TestGeom.h</includes>
  </compound>
  <compound kind="file">
    <name>TestGeom.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestGeom_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="Point_8h" name="Point.h" local="yes" imported="no">Point.h</includes>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <includes id="Orthant_8h" name="Orthant.h" local="yes" imported="no">Orthant.h</includes>
    <includes id="OrthantList_8h" name="OrthantList.h" local="yes" imported="no">OrthantList.h</includes>
    <includes id="HyperCube_8h" name="HyperCube.h" local="yes" imported="no">HyperCube.h</includes>
    <includes id="HyperPlane_8h" name="HyperPlane.h" local="yes" imported="no">HyperPlane.h</includes>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>TestODEintegrator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestODEintegrator_8cpp</filename>
    <includes id="TestODEintegrator_8h" name="TestODEintegrator.h" local="yes" imported="no">TestODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>TestODEintegrator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestODEintegrator_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PointODEintegrator_8h" name="PointODEintegrator.h" local="yes" imported="no">PointODEintegrator.h</includes>
    <includes id="IntervalODEintegrator_8h" name="IntervalODEintegrator.h" local="yes" imported="no">IntervalODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>TestPropagationPattern.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestPropagationPattern_8cpp</filename>
    <includes id="PropagationPattern_8h" name="PropagationPattern.h" local="yes" imported="no">PropagationPattern.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>TestPropagationPattern_8cpp.shtml</anchorfile>
      <anchor>ae66f6b31b5ad750f1fe042a706a4e3d4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TestSBrateEvaluator.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestSBrateEvaluator_8cpp</filename>
    <includes id="TestSBrateEvaluator_8h" name="TestSBrateEvaluator.h" local="yes" imported="no">TestSBrateEvaluator.h</includes>
  </compound>
  <compound kind="file">
    <name>TestSBrateEvaluator.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestSBrateEvaluator_8h</filename>
    <includes id="sdscip_8h" name="sdscip.h" local="yes" imported="no">sdscip.h</includes>
    <includes id="SBrateEvaluator_8h" name="SBrateEvaluator.h" local="yes" imported="no">SBrateEvaluator.h</includes>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>TestSDplugin.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestSDplugin_8cpp</filename>
    <includes id="TestSDplugin_8h" name="TestSDplugin.h" local="yes" imported="no">TestSDplugin.h</includes>
  </compound>
  <compound kind="file">
    <name>TestSDplugin.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestSDplugin_8h</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PointODEintegrator_8h" name="PointODEintegrator.h" local="yes" imported="no">PointODEintegrator.h</includes>
    <includes id="IntervalODEintegrator_8h" name="IntervalODEintegrator.h" local="yes" imported="no">IntervalODEintegrator.h</includes>
    <includes id="PointRateEvaluator_8h" name="PointRateEvaluator.h" local="yes" imported="no">PointRateEvaluator.h</includes>
    <includes id="SDSCIPtest_8h" name="SDSCIPtest.h" local="yes" imported="no">SDSCIPtest.h</includes>
  </compound>
  <compound kind="file">
    <name>TestStatistics.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestStatistics_8cpp</filename>
    <includes id="TestStatistics_8h" name="TestStatistics.h" local="yes" imported="no">TestStatistics.h</includes>
  </compound>
  <compound kind="file">
    <name>TestStatistics.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>TestStatistics_8h</filename>
    <includes id="Statistics_8h" name="Statistics.h" local="yes" imported="no">Statistics.h</includes>
    <includes id="BaseTest_8h" name="BaseTest.h" local="yes" imported="no">BaseTest.h</includes>
  </compound>
  <compound kind="file">
    <name>unittests.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>unittests_8cpp</filename>
    <includes id="ProbDataSD_8h" name="ProbDataSD.h" local="yes" imported="no">ProbDataSD.h</includes>
    <includes id="PropOBRA_8h" name="PropOBRA.h" local="yes" imported="no">PropOBRA.h</includes>
    <includes id="HeurSimODE_8h" name="HeurSimODE.h" local="yes" imported="no">HeurSimODE.h</includes>
    <includes id="BranchControlFirst_8h" name="BranchControlFirst.h" local="yes" imported="no">BranchControlFirst.h</includes>
    <includes id="PropODE_8h" name="PropODE.h" local="yes" imported="no">PropODE.h</includes>
    <includes id="ReaderVOP_8h" name="ReaderVOP.h" local="yes" imported="no">ReaderVOP.h</includes>
    <includes id="PresolConsGraph_8h" name="PresolConsGraph.h" local="yes" imported="no">PresolConsGraph.h</includes>
    <includes id="Statistics_8h" name="Statistics.h" local="yes" imported="no">Statistics.h</includes>
    <includes id="BaseTest_8h" name="BaseTest.h" local="yes" imported="no">BaseTest.h</includes>
    <includes id="TestGeom_8h" name="TestGeom.h" local="yes" imported="no">TestGeom.h</includes>
    <includes id="TestODEintegrator_8h" name="TestODEintegrator.h" local="yes" imported="no">TestODEintegrator.h</includes>
    <includes id="TestSBrateEvaluator_8h" name="TestSBrateEvaluator.h" local="yes" imported="no">TestSBrateEvaluator.h</includes>
    <includes id="TestBoundMap_8h" name="TestBoundMap.h" local="yes" imported="no">TestBoundMap.h</includes>
    <includes id="TestExprPiecewiseLinear_8h" name="TestExprPiecewiseLinear.h" local="yes" imported="no">TestExprPiecewiseLinear.h</includes>
    <includes id="TestEstimatorTypes_8h" name="TestEstimatorTypes.h" local="yes" imported="no">TestEstimatorTypes.h</includes>
    <includes id="TestStatistics_8h" name="TestStatistics.h" local="yes" imported="no">TestStatistics.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>unittests_8cpp.shtml</anchorfile>
      <anchor>a3c04138a5bfe5d72780bb7e82a18e627</anchor>
      <arglist>(int argc, char **argv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Vector.cpp</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Vector_8cpp</filename>
    <includes id="Vector_8h" name="Vector.h" local="yes" imported="no">Vector.h</includes>
    <member kind="function">
      <type>Vector</type>
      <name>operator+</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>af0699c79435db7f608964ab825b2ffd4</anchor>
      <arglist>(Vector lhs, Vector const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator-</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a2a750282191154a49bc6e2183f3db406</anchor>
      <arglist>(Vector lhs, Vector const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a67240dccd723d3114fee7565d246cefd</anchor>
      <arglist>(Vector lhs, double rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>ae1031e1f5df40bb2d0421e7a8033b4ad</anchor>
      <arglist>(double lhs, Vector rhs)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a35bec1971c45e7d6b1359586ac20afd8</anchor>
      <arglist>(Vector lhs, Vector rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Vector.h</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>Vector_8h</filename>
    <includes id="Point_8h" name="Point.h" local="yes" imported="no">Point.h</includes>
  </compound>
  <compound kind="file">
    <name>xternal.c</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/doc/</path>
    <filename>xternal_8c</filename>
  </compound>
  <compound kind="struct">
    <name>Bound</name>
    <filename>structBound.shtml</filename>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>var</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>aada82de4056159b7048abba3e1fedbe8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>newval</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a91d442dba177b30f215c045b7b0b7638</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>improvement</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a1ac7e065de4239b45c341068240e91f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_BOUNDTYPE</type>
      <name>boundtype</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a645b89d618513ef103d877828709d144</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>score</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a374b23f2207dba6a826b1e0820a4701e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>filtered</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a63acef6d134048c71264bba184878e9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>found</name>
      <anchorfile>structBound.shtml</anchorfile>
      <anchor>a77dd688bc046432e2057ba249f592e61</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BoundGroup</name>
    <filename>structBoundGroup.shtml</filename>
    <member kind="variable">
      <type>int</type>
      <name>firstbdindex</name>
      <anchorfile>structBoundGroup.shtml</anchorfile>
      <anchor>af7d260c4bbad7f7a9b25f4d554457a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nbounds</name>
      <anchorfile>structBoundGroup.shtml</anchorfile>
      <anchor>a04292a47e9f3fefaf5862035d16cd1cb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BoundMapHelpers</name>
    <filename>classBoundMapHelpers.shtml</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BoundMapHelpers</name>
      <anchorfile>classBoundMapHelpers.shtml</anchorfile>
      <anchor>a533c15be3c8258be564082174c53f282</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ListNode</name>
    <filename>classListNode.shtml</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a8ed5351018716cf9a8b6cc1e912434a7</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>ListNode &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70fd571e49c73c9cd268a61baf8f8c25</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a30c7b4104997f51657ec4feb79630d31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a4fe22b1cb664bd14a92f271ebc2318b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a2714d7667fe71476aa50a19e912c5393</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>ad813529940dd34ea30577989995eea40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>adb9fc17f48472916ac48c48019848be8</anchor>
      <arglist>(T *next)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>af4de41c42b3edd1183108aad304b30e3</anchor>
      <arglist>(T *prev)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a43a2fd9b239bd1bfe83e0306790417bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>abe41245574baa42781b71f70e49fd06b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a07ce4c6d62f8734a023d7b3d3cedea12</anchor>
      <arglist>(ListNode&lt; T &gt; &amp;&amp;other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ListNode&lt; T &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70f72371a142cf30ec17c4005eaeb33a</anchor>
      <arglist>(ListNode&lt; T &gt; &amp;&amp;other)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LookupConsHdlr</name>
    <filename>classLookupConsHdlr.shtml</filename>
    <member kind="function">
      <type></type>
      <name>LookupConsHdlr</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a2486c04bad03c87757bd328610553a36</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LookupConsHdlr</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a32d494a0c65a1840e77887906713105d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_EVENTEXEC</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a577b552300e77d944cb2e2969495c253</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSDELETE</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a7e10203e089ffcaf3e4ab88f00ce06b3</anchor>
      <arglist>(scip_delete)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSTRANS</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>ac6065ce4926117cfb885da40f4556b30</anchor>
      <arglist>(scip_trans)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSSEPALP</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a1dac4c299e15a8f5c6daa0f5d741f837</anchor>
      <arglist>(scip_sepalp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSSEPASOL</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a744907977b99649033b037ecdb6cc187</anchor>
      <arglist>(scip_sepasol)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSENFOLP</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>ae5ce7ec092abf98473ba109e00941486</anchor>
      <arglist>(scip_enfolp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSENFOPS</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a013b9893659b1df2e33348a315caca91</anchor>
      <arglist>(scip_enfops)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSCHECK</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a88e4b99efe7b8a094d1e3393dede2e5f</anchor>
      <arglist>(scip_check)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSPROP</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>afed9caa83af31eafbb201242e42cc22d</anchor>
      <arglist>(scip_prop)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSLOCK</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a5d8858005a915e4ad9e8c2cd0f174c99</anchor>
      <arglist>(scip_lock)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSDELVARS</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a6e8cbecdde3a369748ee0cc5e6d90b98</anchor>
      <arglist>(scip_delvars)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSPRINT</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a4365fb83a66b237e63f3d36707571176</anchor>
      <arglist>(scip_print)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSHDLRISCLONEABLE</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a08d35899ee266818a0b4ea988436c2a1</anchor>
      <arglist>(iscloneable)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSHDLRCLONE</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>a4caeaa93ab86d60613e1173035c60b6e</anchor>
      <arglist>(scip::ObjProbCloneable *clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_CONSCOPY</name>
      <anchorfile>classLookupConsHdlr.shtml</anchorfile>
      <anchor>af3fc1531d72b36c31a10bcb5748026df</anchor>
      <arglist>(scip_copy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MdlExpressionTranslator</name>
    <filename>classMdlExpressionTranslator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>MdlExpressionTranslator</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>ac2e4c0bc00515755f7bb36917e736792</anchor>
      <arglist>(SCIP *_scip, sdo::ExpressionGraph &amp;_exprGraph, const LookupMap &amp;_lkpMap)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MdlExpressionTranslator</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a96167c46b70cdbc18ddd20071de2ae6b</anchor>
      <arglist>(const MdlExpressionTranslator &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MdlExpressionTranslator</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>ac2a6730c7346acb9b6ffd7b550a6029e</anchor>
      <arglist>(MdlExpressionTranslator &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MdlExpressionTranslator</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a1407665b78308c10f37b443222453409</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>getScipExpr</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a07d7cefc1b1d9ac7f8230cef86e76ee9</anchor>
      <arglist>(sdo::ExpressionGraph::Node *root, SCIP_EXPR **expr, bool initial=false, bool allowrootvar=false)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR *</type>
      <name>getVarExpr</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a6bfa3da57305bf35053d20900f6ec31d</anchor>
      <arglist>(sdo::ExpressionGraph::Node *varnode)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>getParameterValues</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a5d3ad4650c63dd8a349ce9ebdb468bf2</anchor>
      <arglist>(double time, bool initial=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>getParameterValues</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a18227a3cd238ed2b6eb4ec6816c6c929</anchor>
      <arglist>(int time, bool initial=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; sdo::ExpressionGraph::Node * &gt;</type>
      <name>getParameterNodes</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>acf5ed8d3ea7a8e45f7ac97b660cc6eb2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setVars</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>aed95079bb74e579ca2140615d3a3605e</anchor>
      <arglist>(const std::vector&lt; MdlScipVar &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setVars</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>abd6d275577ba20904cf0e8fe717af900</anchor>
      <arglist>(const std::vector&lt; MdlScipVar &gt; &amp;vec, const std::vector&lt; SCIP_EXPR * &gt; &amp;varexpr)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; MdlScipVar &gt;</type>
      <name>createVariableMapping</name>
      <anchorfile>classMdlExpressionTranslator.shtml</anchorfile>
      <anchor>a52737df29af24a9d1c89880be02e5529</anchor>
      <arglist>(const sdo::Objective &amp;objective, bool minimal, bool cmpvar=true, bool ratealgebraic=false, bool isolatelookups=false)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MdlScipVar</name>
    <filename>structMdlScipVar.shtml</filename>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getLb</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a2459643e641eebd040b77398fd477364</anchor>
      <arglist>(SCIP *scip) const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getUb</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>afe899d7ed6f10aead38e28e829768791</anchor>
      <arglist>(SCIP *scip) const </arglist>
    </member>
    <member kind="variable">
      <type>sdo::ExpressionGraph::Node *</type>
      <name>node</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a07fb580ce1cd4fa375167e38e4d4351c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>ab41074578ba3ebcf8fef3ca81d742123</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>idx</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a91b1da4148af36c784e1400e498a9eac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VARTYPE</type>
      <name>type</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a0beaf058bfde139b66946274b14a42d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>mayer_coeff</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a09f076fe4365a189ff4c81bd95b23a85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>lagrange_coeff</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a60fb5a4d9add6cc7ebeea091acd93c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>negative</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a3e7c38b846c62b428567ce43509dc3fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>positive</name>
      <anchorfile>structMdlScipVar.shtml</anchorfile>
      <anchor>a0a4b8d173de6872e20ae5d5818e43e0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NLPGraph</name>
    <filename>classNLPGraph.shtml</filename>
    <member kind="typedef">
      <type>lemon::ListGraph::Node</type>
      <name>VarNode</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>aef289667ea305552ae66b815ae56b018</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>lemon::ListGraph::Node</type>
      <name>ConsNode</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>af52eb555d0f4aee89c34290d5ab4aca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>lemon::ListGraph::Edge</type>
      <name>Edge</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a60f888a59a5bab7cccb3948be0501b10</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>lemon::ListGraph::Node</type>
      <name>Node</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>ac856610e0577c1bec6f40621b781d1e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>lemon::ListGraph::NodeIt</type>
      <name>NodeIt</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a1c2d7cde931f5103020a3ec3354de712</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NLPGraph</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>aaf863d364f94cfe762cc60a778963e35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NLPGraph</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>adf43488444713e74909680aa22bd7f8d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcConsOrders</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a9de87810f858dd2883177d4003632578</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>order</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a534c685903f536ec972e7d8fb7741a40</anchor>
      <arglist>(Node) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>nonFixedOrder</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a58a32f00235e133a92e4f048fd524382</anchor>
      <arglist>(Node n) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcPropagationSequence</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>af22fa7991a04a6163c1fef6a299f2c2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcFixedEdges</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>acc2945bb83f974971eb23f5b2b44aad5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcNonFixedOrders</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a98043f9853779c515b1619a999fa1a59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fix</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a474ea7b3fd8626f5dbf9874dd3bbc2d4</anchor>
      <arglist>(Node n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fix</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a99a6e1558832bab63f3ac3326961e8f0</anchor>
      <arglist>(Node n, int step)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFixed</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>adbf2ea03ee36507d3aa4954084d2998d</anchor>
      <arglist>(Node varNode) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFixed</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>ab1eaa8b8223ece614846a05a1cf1e94f</anchor>
      <arglist>(Edge edge) const </arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>addCons</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a931dde5cbc5bd68e725670c98819a193</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>addCons</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a423ed483b1b29770de947488667e36c4</anchor>
      <arglist>(std::string _name, SCIP_CONS *_consPointer)</arglist>
    </member>
    <member kind="function">
      <type>Edge</type>
      <name>addEdge</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>aef323c3c5a04514d5fd2988b6f015d36</anchor>
      <arglist>(Node _constraint, Node _variable)</arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>showVar</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>adeef2971cbb3545c5a1b5456c66d9912</anchor>
      <arglist>(SCIP_VAR *_varPointer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printNodes</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a8afa0d31d76d6b5ab0ecee0f6af53580</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeGraph</name>
      <anchorfile>classNLPGraph.shtml</anchorfile>
      <anchor>a94a67ff5d4fa31889a5d88899af62924</anchor>
      <arglist>(std::string filename) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PresolConsGraph</name>
    <filename>classPresolConsGraph.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PresolConsGraph</name>
      <anchorfile>classPresolConsGraph.shtml</anchorfile>
      <anchor>aa628afaa49c3ee4db8caa12626d8f73d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PresolConsGraph</name>
      <anchorfile>classPresolConsGraph.shtml</anchorfile>
      <anchor>abc17f7f3b08caf1aeb343bf23c046fe8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PRESOLEXEC</name>
      <anchorfile>classPresolConsGraph.shtml</anchorfile>
      <anchor>aa96ddb0b7aac1e521df593c7f5f79bb0</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PresolCppMin</name>
    <filename>classPresolCppMin.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PresolCppMin</name>
      <anchorfile>classPresolCppMin.shtml</anchorfile>
      <anchor>aab781b31d9d461948b3b84cfc67d66bd</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PresolCppMin</name>
      <anchorfile>classPresolCppMin.shtml</anchorfile>
      <anchor>a4920b133bc9678aab3f60617c74e9874</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PRESOLEXEC</name>
      <anchorfile>classPresolCppMin.shtml</anchorfile>
      <anchor>a287eafa4a81ef69dcc0caa05e122b48f</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PropagationPattern</name>
    <filename>classPropagationPattern.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PropagationPattern</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a38fb719e5b969cb130dd941d617ea1ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PropagationPattern</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a77d0af4e7ea3543cbae6405de433554a</anchor>
      <arglist>(int _confType)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PropagationPattern</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ac8841300021560ac1b09ea93c280dddc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addVar</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a8dc329a329fda869e25e4d9c895fba92</anchor>
      <arglist>(SCIP_VAR *scipVar, SCIP_VAR *subscipVar)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addStruct</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ad12f74dd2ec439d57c0e31ac29e4d0a1</anchor>
      <arglist>(test_struct *)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>configurationsLeft</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>abfc64411a95f155278134634f8d57f13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>fetchPattern</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a45eb050fe8bd05df6a9bb074cc29f670</anchor>
      <arglist>(int ndim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearVars</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a296dfa6a34d0b38e86f2742211a1b315</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSubscip</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>aca801b0c1d5f3a573528dcd550435d80</anchor>
      <arglist>(SCIP *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setScip</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ab75449fea194ede97d2e51f8389b2968</anchor>
      <arglist>(SCIP *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCurrentTime</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a1c11ec43a478fe0f673f9ae89cdb71ef</anchor>
      <arglist>(int currentTime)</arglist>
    </member>
    <member kind="function">
      <type>SCIP *</type>
      <name>getSubscip</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a70c2650996c08afd7c9de4af05283aad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP *</type>
      <name>getScip</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>aebbf1c9172775655f448994f92efe631</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>start</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a9056809019f8ee5705201439f02aae00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>next</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a0f8e8eb2f8219f2711de1da10716b93a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>toString</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a3d5f6c695622b4105c9843a1a1bb3f1e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>confString</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a6927fee8dbdc8f46bff559ec6e1ceed5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ensureValidPattern</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a4cf6a15dc583a941c47f053beb7fea3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>updateIsCut</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ace13d2ca536a95be3d01bd0dfee3e744</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isCut</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ab809411eea6662fc3e6586f6e0bc406d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>cutIsUseful</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>adfb1eaa48b79336c1cffd2f1b6e93373</anchor>
      <arglist>(SCIP_Real rhs, SCIP_Bool *isUseful)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCurrentDim</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a263e2ca798de8794c9c692ba14f50691</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; SDSCIP_PROPDIR, VarPair &gt;</type>
      <name>getBoundVar</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a424858f57baf7f8d9d43f29cd7734b3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setScipVarsArray</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a0711148d3a9a6dc246408bd13b110b7d</anchor>
      <arglist>(SCIP_VAR **vars) const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>updateSubscipSolutionVector</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a1e39064b4548f4ddcccfed473964061c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setSubscipVarsArray</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ae905517ff448481b96a5a27d94057165</anchor>
      <arglist>(SCIP_VAR **vars) const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setValsArray</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a9e76884d96119208e1f402a43ab900c6</anchor>
      <arglist>(SCIP_Real *vals)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setAddCuts</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>acdbe08bc8dd0d860008e3f6b7f1fd3f9</anchor>
      <arglist>(SCIP_Bool addCuts)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setSolMap</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>ad2ae3e5013fd55d2f5ccee496e0731d2</anchor>
      <arglist>(std::map&lt; SCIP_VAR *, SCIP_Real &gt; *solMap)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setCutConf3d</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a500cecb420ce447c1d31da9e6dcf1b0d</anchor>
      <arglist>(int confId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setUseUnitCuts</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>acb7ffde481aaf2897fd8d3cfd17eaffc</anchor>
      <arglist>(SCIP_Bool useUnitCuts)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>propagate</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>adaf8a731b0be3edbd21a5bd5eb01b919</anchor>
      <arglist>(int currentTime)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getCutString</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>afe98e508df71a8c3194c957977b13106</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>resetObjVals</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a8594e7370f23551cf959d3363d018e84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>buildHyperCube</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a159488c5b55e861e06aec4c73649ad0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Statistics</type>
      <name>stats_</name>
      <anchorfile>classPropagationPattern.shtml</anchorfile>
      <anchor>a5b8c8e8c9eab536af2703d497c6a054b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCIP_ConsData</name>
    <filename>structSCIP__ConsData.shtml</filename>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>forwardVar</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>ae6ff89b8c5284ebdd519140f5d543172</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>arg</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>a4b9334a0a2c2aabac3cd801fd98751d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>propagated</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>afd87739ac96d5d64b9dd1092600292de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 3 &gt; &gt;</type>
      <name>lookup</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>afc5b4d45c8e8d86d27f1ec84eb0c8e2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::shared_ptr&lt; spline::PiecewisePolynomial&lt; 2 &gt; &gt;</type>
      <name>derivate</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>a3aa8f388c38a861da3f496725965baae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::shared_ptr&lt; spline::PiecewiseLinear &gt;</type>
      <name>linearModel</name>
      <anchorfile>structSCIP__ConsData.shtml</anchorfile>
      <anchor>ad58acd3a4e8e659e84fe0560e5ea117e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCIP_EventData</name>
    <filename>structSCIP__EventData.shtml</filename>
    <member kind="variable">
      <type>SCIP_CONSDATA *</type>
      <name>consdata</name>
      <anchorfile>structSCIP__EventData.shtml</anchorfile>
      <anchor>aa0a0289e801e8d82b91d286dad893b5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>filterpos</name>
      <anchorfile>structSCIP__EventData.shtml</anchorfile>
      <anchor>a16715cccde897d21183ce13b20505c82</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCIP_ProbData</name>
    <filename>structSCIP__ProbData.shtml</filename>
    <member kind="variable">
      <type>sdscip::SDproblemStructureInterface *</type>
      <name>structure</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>ab43410f9d368c7403b12f0799e0b1b76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PropCutMap *</type>
      <name>propCuts</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>a47970e5008ce5851a30b8d254b4fd6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isReformulated</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>a62cf6846b25fe2141eba32e99dfe6609</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isStructureValid</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>ac54770e9364ff8fc9786fbc0a1d61e75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::regex *</type>
      <name>varRegex</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>af3da771d83961e34ba4efb0cfda9512c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::regex *</type>
      <name>consRegex</name>
      <anchorfile>structSCIP__ProbData.shtml</anchorfile>
      <anchor>a72a2600aec4ea3795f729c687a5eb2b7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCIP_PropData</name>
    <filename>structSCIP__PropData.shtml</filename>
    <member kind="variable">
      <type>BOUND **</type>
      <name>bounds</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ae521e00cd184d485bb82aa333e3048fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; BOUND &gt;</type>
      <name>foundboundchanges</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ae66d0a6bfe42fe1566842bdcf73d21bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BOUNDGROUP *</type>
      <name>boundgroups</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a212c7a362875b7a5418517f67ac00ee6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_ROW *</type>
      <name>cutoffrow</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ac3108e2c1722e96ef64b7e5c89597f8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_PROP *</type>
      <name>genvboundprop</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>adae9918ec6a619f506a4cb7ca32bde52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Longint</type>
      <name>lastnode</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a67cb2abc59f8f7dba2764880df367aae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>dualfeastol</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ac9e70d28bf2938a2c76809f6f29e9325</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>conditionlimit</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a0459f1bf88de74302f12a2345f54c7f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>itlimitfactor</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a9e55778004f22014ff7ef1b87f669c0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>applyfilterrounds</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a131168424ff345e0a2d3848e0a190cc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>creategenvbounds</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a20a12654d4bf845589c0371be7c8a704</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>normalize</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ad2776cb312d1e878c3df0685400cd4e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>maxlookahead</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>aba582040ffd05743b78245d7040c8110</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nbounds</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>ad1a2d3c824b34b3d0daa0e33d7ebccaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nboundgroups</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>afa0adc2cb03a32b34f213690ae2de9c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nminfilter</name>
      <anchorfile>structSCIP__PropData.shtml</anchorfile>
      <anchor>a2d0f2c483ee70e5ce18d2231f9542ea9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCIP_UserExprData</name>
    <filename>structSCIP__UserExprData.shtml</filename>
    <member kind="variable">
      <type>shared_ptr&lt; spline::BSplineCurve&lt; 3, SCIP_Real &gt; &gt;</type>
      <name>lookup</name>
      <anchorfile>structSCIP__UserExprData.shtml</anchorfile>
      <anchor>a8f22391e241601edf40daf644d67db61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt;</type>
      <name>lookup</name>
      <anchorfile>structSCIP__UserExprData.shtml</anchorfile>
      <anchor>aa9065c4ad31a361a91a11516aaee0acc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>identifier</name>
      <anchorfile>structSCIP__UserExprData.shtml</anchorfile>
      <anchor>ac5a7ba2f1b0934fecc54fd92348fad86</anchor>
      <arglist>[10]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SDCons</name>
    <filename>classSDCons.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a5dc85f5c4996bb073c07a6032c99fc09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>adc2fa2ad3c1f8c710c226a5ff0ef122b</anchor>
      <arglist>(SCIP_CONS *c)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a55952f0c379c41dd4dc9a51a0d5bac76</anchor>
      <arglist>(SDConsType type, SDConstMinMax *c)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>aacaa4b51d9202a68501b806cc3eb8bd6</anchor>
      <arglist>(const SDCons &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>SDCons &amp;</type>
      <name>operator=</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a8be34756d60d17b1004afa702a4b8412</anchor>
      <arglist>(const SDCons &amp;other)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a695b058f2c0f0d3da74afae8b5e53e10</anchor>
      <arglist>(SDCons &amp;&amp;other)</arglist>
    </member>
    <member kind="function">
      <type>SDCons &amp;</type>
      <name>operator=</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>aa7be168730826d18ac7dfded8c399efb</anchor>
      <arglist>(SDCons &amp;&amp;other)</arglist>
    </member>
    <member kind="function">
      <type>SDConsType</type>
      <name>getType</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a2ca6a707e3cf898df3e84a092f9d8ddf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getScipTopLevelCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a5c3a70043ab341e631785177c6fd586f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SDMinMax *</type>
      <name>getSDMinMaxConsData</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>aff451314275a9107abe2e9b1f3411a6a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SDConstMinMax *</type>
      <name>getSDConstMinMaxConsData</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a2c133930333f4e3666267096efc6d33c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SDCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>acea8adce9bee25f1c8eb92a7d20b7133</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SDCons</type>
      <name>CreateConstMin</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a23f25036cb5d52a3c32799135d8f6076</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SDCons</type>
      <name>CreateConstMax</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a161fd9c1365a35a26eaa631150c8194c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend SCIP_RETCODE</type>
      <name>CreateMinMaxCons</name>
      <anchorfile>classSDCons.shtml</anchorfile>
      <anchor>a34bc2d8ebfb624222687be8f57eff8cc</anchor>
      <arglist>(SCIP *scip, SDCons *sdcons, SDConsType type, SCIP_VAR *forward_var, SCIP_VAR *arg0, SCIP_VAR *arg1)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDConstMinMax</name>
    <filename>structSDConstMinMax.shtml</filename>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>var_pos</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>a9ed3730b2368962319eb2a390aa7fd13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>var_neg</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>af156ce70286b693d9aef17f069691eb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>var_bin</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>a897815db9b80ad805d912714913b5c05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>cons</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>afea115c078d0e8b2e2f395d280e97990</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>splitter</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>a976902cc38e8fa4eab1b174c04b30878</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>max_cons</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>ad294edf1d9938e7b599686c22b20eeeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>min_cons</name>
      <anchorfile>structSDConstMinMax.shtml</anchorfile>
      <anchor>a9e6983c5543b02a2ea006ebea1b049cf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SDControl</name>
    <filename>classSDControl.shtml</filename>
    <class kind="struct">SDControl::CompareStartTime</class>
    <class kind="struct">SDControl::CompareTime</class>
    <member kind="function">
      <type></type>
      <name>SDControl</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>a8fac6a54d0577eca020682bc8547e460</anchor>
      <arglist>(int time_begin, int time_end, SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>const SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>a8a686fb35f113d616902d06386103b4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>getScipVarName</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>a90b19c75c7971e26d3bdb969383df803</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>ae17480cbcf751c2d6e8ce8d2a8bb25eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getTimeBegin</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>a1298b8c2009eb3f3b115e8bc16505d08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getTimeEnd</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>ac980bb26971782a9a0189f2b222f02f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>aec994afc0ea68c87a65e52e51de0946c</anchor>
      <arglist>(const SDControl &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>abbd3283dd632952d8bfde2595adea37c</anchor>
      <arglist>(int time) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a8ed5351018716cf9a8b6cc1e912434a7</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>ListNode &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70fd571e49c73c9cd268a61baf8f8c25</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>const SDControl *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a30c7b4104997f51657ec4feb79630d31</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SDControl *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a4fe22b1cb664bd14a92f271ebc2318b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SDControl *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a2714d7667fe71476aa50a19e912c5393</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SDControl *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>ad813529940dd34ea30577989995eea40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>adb9fc17f48472916ac48c48019848be8</anchor>
      <arglist>(SDControl *next)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>af4de41c42b3edd1183108aad304b30e3</anchor>
      <arglist>(SDControl *prev)</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDControl.shtml</anchorfile>
      <anchor>a564caa189c30e5838ab8978b143cc245</anchor>
      <arglist>(const int time, const SDControl &amp;var)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a43a2fd9b239bd1bfe83e0306790417bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a07ce4c6d62f8734a023d7b3d3cedea12</anchor>
      <arglist>(ListNode&lt; SDControl &gt; &amp;&amp;other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ListNode&lt; SDControl &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70f72371a142cf30ec17c4005eaeb33a</anchor>
      <arglist>(ListNode&lt; SDControl &gt; &amp;&amp;other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>abe41245574baa42781b71f70e49fd06b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDControl::CompareStartTime</name>
    <filename>structSDControl_1_1CompareStartTime.shtml</filename>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareStartTime.shtml</anchorfile>
      <anchor>ad5e61314c6566700a5fc637d228d525d</anchor>
      <arglist>(int time, const SDControl &amp;c) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareStartTime.shtml</anchorfile>
      <anchor>a0c7c6779a7bcc7256bd8f1747537cd5b</anchor>
      <arglist>(const SDControl &amp;c, int time) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareStartTime.shtml</anchorfile>
      <anchor>a5be7a2fcf2db188beb8f6b2eca40428d</anchor>
      <arglist>(const SDControl &amp;c1, const SDControl &amp;c2) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDControl::CompareTime</name>
    <filename>structSDControl_1_1CompareTime.shtml</filename>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareTime.shtml</anchorfile>
      <anchor>a814eccdb6ab1bf5e3abf5e0635034a01</anchor>
      <arglist>(int time, const SDControl &amp;c) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareTime.shtml</anchorfile>
      <anchor>acb17f090a6121df83c56770e5bf5c38d</anchor>
      <arglist>(const SDControl &amp;c, int time) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structSDControl_1_1CompareTime.shtml</anchorfile>
      <anchor>aa8a3b43177e84cbd0ea10433c4e8a988</anchor>
      <arglist>(const SDControl &amp;c1, const SDControl &amp;c2) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SDList</name>
    <filename>classSDList.shtml</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::iterator</type>
      <name>iterator</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>af9f5ca77ca74f5f63fb2329bfca099cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a5231d58ff47a1eb5b48678492e81009d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>ab6c208903ee135b9b6960f9d369865d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a1934924c7627befc1be9679c8264174e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDList</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a9b45eede0a402d52b2a0aa023b4d01b8</anchor>
      <arglist>(SDListBuilder&lt; T, VAR_ID &gt; &amp;builder)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDList</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a8a795a058f8c8d74183cc2a76ae57fa9</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>std::size_t</type>
      <name>size</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a751d111918aa87b86a73d6acea4e167b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>abfb12df91d7b6115f621934d9af5c828</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>ac94277ffc3825f81b107cf8e243c99a6</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a76f6ba8de0a1b43a435198088253c372</anchor>
      <arglist>(int time) const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a684a40fbf1286bb60568a9788db18bfa</anchor>
      <arglist>(int time) const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a49e60b9f46868fd17c2c81323fb084b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a32648e8129c84f9a304ec89459ad772f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a8bee0ae77e6ec942b7e9b9f594f60e2c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a465339692252e4d0819df047f94d0845</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a2083a461a55469748f809d1bae2e747a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SDList&lt; SDControl &gt;::iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a9c3167b709473af625f930e018cdeb0a</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>SDList&lt; SDControl &gt;::const_iterator</type>
      <name>end</name>
      <anchorfile>classSDList.shtml</anchorfile>
      <anchor>a41198306547add971fb3a6305af83b68</anchor>
      <arglist>(int time) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SDListBuilder</name>
    <filename>classSDListBuilder.shtml</filename>
    <templarg>T</templarg>
    <templarg>VAR_ID</templarg>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>classSDListBuilder.shtml</anchorfile>
      <anchor>a2f4e4cccaa5f23db1255660dc922d404</anchor>
      <arglist>(const VAR_ID &amp;symb, Args &amp;&amp;...args)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; T &gt;</type>
      <name>build</name>
      <anchorfile>classSDListBuilder.shtml</anchorfile>
      <anchor>a2cc43099bda2665382c6bb13ddbe9b5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classSDListBuilder.shtml</anchorfile>
      <anchor>a6f94cfdabd9cde9024ae8f6bb171429e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDListTraits</name>
    <filename>structSDListTraits.shtml</filename>
    <templarg>T</templarg>
    <templarg>VAR_ID</templarg>
    <member kind="typedef">
      <type>void</type>
      <name>key_t</name>
      <anchorfile>structSDListTraits.shtml</anchorfile>
      <anchor>a722a6010f10ffbcb4c9144b02ef9aa80</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDListTraits&lt; SDControl, VAR_ID &gt;</name>
    <filename>structSDListTraits_3_01SDControl_00_01VAR__ID_01_4.shtml</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>std::tuple&lt; VAR_ID, int, int &gt;</type>
      <name>key_t</name>
      <anchorfile>structSDListTraits_3_01SDControl_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>a02bcdf397985f3d4443b68c63c5ab518</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_key</name>
      <anchorfile>structSDListTraits_3_01SDControl_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>ace885c1bf4ea928a8ed19e384355dfd6</anchor>
      <arglist>(const VAR_ID &amp;s, const SDControl &amp;val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_prev_key</name>
      <anchorfile>structSDListTraits_3_01SDControl_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>a44c51712dd7c5e1e11f2f59625f44569</anchor>
      <arglist>(const key_t &amp;k)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_next_key</name>
      <anchorfile>structSDListTraits_3_01SDControl_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>ad81bb8c0fa6ece53d4f052c9e0f97e61</anchor>
      <arglist>(const key_t &amp;k)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDListTraits&lt; SDVariable, VAR_ID &gt;</name>
    <filename>structSDListTraits_3_01SDVariable_00_01VAR__ID_01_4.shtml</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>std::tuple&lt; VAR_ID, int, int &gt;</type>
      <name>key_t</name>
      <anchorfile>structSDListTraits_3_01SDVariable_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>a36cc6c7f33a46a0fc3dd92b52186d66c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_key</name>
      <anchorfile>structSDListTraits_3_01SDVariable_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>a21e364db34ad03d09c037cae2907331b</anchor>
      <arglist>(const VAR_ID &amp;s, const SDVariable &amp;val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_prev_key</name>
      <anchorfile>structSDListTraits_3_01SDVariable_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>abe7dabd9db0884a6e4b287c328c520d1</anchor>
      <arglist>(const key_t &amp;k)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static key_t</type>
      <name>get_next_key</name>
      <anchorfile>structSDListTraits_3_01SDVariable_00_01VAR__ID_01_4.shtml</anchorfile>
      <anchor>a22e43f46e56d5ee1c820004bce8d58c6</anchor>
      <arglist>(const key_t &amp;k)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SDMinMax</name>
    <filename>structSDMinMax.shtml</filename>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>arg0</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>acb59d2997a7dffa89bd978d9bf9113ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>pos0</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a96a977874a6e7627f6e2bbb179251bb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>neg0</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>afbcdc40c8e1f69fdf0610107a272990d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>split0</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a9560d02d5d7c88e03e7302f986933dfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>arg1</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>ac078115dc4713fd1e781c81161c9ae7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>pos1</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a7faa2ad526a90556331520c4cc39d224</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>neg1</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>aa6f2c4a9c37b148d59809c435741cc77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>split1</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a9c5aa5923c338a061724ef74ebf2c16a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_VAR *</type>
      <name>select</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a7fec957fdbd4bc25cc30bed290bd85a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>select0_cons</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>ace0ed1d3417bb1cadda87523281679c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>select1_cons</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>a61945bc6ceeab8ab05db2f8d460cfc3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_CONS *</type>
      <name>cons</name>
      <anchorfile>structSDMinMax.shtml</anchorfile>
      <anchor>af5565b8cc7664627a4543ccb89dd0dea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SDVariable</name>
    <filename>classSDVariable.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SDVariable</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a614a2d62573dd6ffb4cb27f4fac6a1c7</anchor>
      <arglist>(int time, int level, SCIP_VAR *var, SDCons cons)</arglist>
    </member>
    <member kind="function">
      <type>const SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>af0faf2f477308cf6853887d63f52a1bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a4893ef6a047d9173acf1562c61e4aaea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SCIP_CONS *</type>
      <name>getScipConstraint</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a4805503456dfb5e37189418e69133d14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getScipConstraint</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>aa1fb79e0254222fb43d3fa454f805ced</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SDCons &amp;</type>
      <name>getConstraint</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a9761d36c8626c4d6b86c30242ac123a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SDCons &amp;</type>
      <name>getConstraint</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a578a8c2325c75a0c7ab5ab4eb3cb07a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getTime</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a7f7b9708298b8627711c8f32e6a8249d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLevel</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>ab60fb6bb4eac3dc3ab6ae7a3b24d6c47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a3c90c8d2474a8dc6f0de6edf6987d026</anchor>
      <arglist>(const SDVariable &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a29b4ea5a3c8303a42654a68432b7ab27</anchor>
      <arglist>(int time) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a8ed5351018716cf9a8b6cc1e912434a7</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>ListNode &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70fd571e49c73c9cd268a61baf8f8c25</anchor>
      <arglist>(const ListNode &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>const SDVariable *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a30c7b4104997f51657ec4feb79630d31</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SDVariable *</type>
      <name>getNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a4fe22b1cb664bd14a92f271ebc2318b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SDVariable *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a2714d7667fe71476aa50a19e912c5393</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SDVariable *</type>
      <name>getPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>ad813529940dd34ea30577989995eea40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNext</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>adb9fc17f48472916ac48c48019848be8</anchor>
      <arglist>(SDVariable *next)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPrev</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>af4de41c42b3edd1183108aad304b30e3</anchor>
      <arglist>(SDVariable *prev)</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;</name>
      <anchorfile>classSDVariable.shtml</anchorfile>
      <anchor>a6626b98f1c2f083048c93495e031d814</anchor>
      <arglist>(const int time, const SDVariable &amp;var)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a43a2fd9b239bd1bfe83e0306790417bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a07ce4c6d62f8734a023d7b3d3cedea12</anchor>
      <arglist>(ListNode&lt; SDVariable &gt; &amp;&amp;other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ListNode&lt; SDVariable &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>a70f72371a142cf30ec17c4005eaeb33a</anchor>
      <arglist>(ListNode&lt; SDVariable &gt; &amp;&amp;other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~ListNode</name>
      <anchorfile>classListNode.shtml</anchorfile>
      <anchor>abe41245574baa42781b71f70e49fd06b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Statistics</name>
    <filename>structStatistics.shtml</filename>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>af09659391046f49a99e44fc1768d403d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggRemainingBounds</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>aea7988975644d8634640bac3e7e9489c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggBoundReduction</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a66881bfbcd89144be11a912783efbccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggGapNonOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a888ee60941481d84b2065938391dce81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggSolutionTime</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>aa3192e88512257e1cd2951dbe801ea96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggCutsSolutionTime</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>aad2616c05960bdc01990e2e19f81320e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>aggDirectSolutionTime</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a62cf3397a0f6e037e3b34a0e03cafa63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nSubscips</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>ae0a1b80df9cd1694071896aab44d4602</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nCuts</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a8fc594483eb1ae6af253b4b2b75ffb39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nDirectBounds</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a30d4afa3215e0ec88ff1b2249a9b8303</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nUpdatedBounds</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a516de0f67865146dbd107cf2220407f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>aad3bc3823314bbfe392d6220bc94adee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nNonOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a9cb2d79e0894f2d7251fb7b3b76ec0a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nCutsOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a46400569bd0fdcc52584f96f1f855fd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nCutsNonOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a43bcd79b1a3218348bea96ab845daabd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nCutsUseful</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a3a9a230a04df6c94e23b4fb5be1a1e33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nDirectOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>a95b1873493a092340a960a88bdb87d4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nDirectNonOptimal</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>ac10f354b1f5674a0436e9dbffe2ffa87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; std::string, int &gt;</type>
      <name>usefulCutDistribution</name>
      <anchorfile>structStatistics.shtml</anchorfile>
      <anchor>aff85ddc6e75700b83ed86731c4b21ce5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>test_struct</name>
    <filename>structtest__struct.shtml</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>eventqueueimpl</name>
      <anchorfile>structtest__struct.shtml</anchorfile>
      <anchor>a88afc79f4a2c85edddebd7a771588ea1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>I4H</name>
    <filename>namespaceI4H.shtml</filename>
    <class kind="class">I4H::BaseTest</class>
    <class kind="class">I4H::Statistics</class>
    <class kind="class">I4H::TestStatistics</class>
  </compound>
  <compound kind="class">
    <name>I4H::BaseTest</name>
    <filename>classI4H_1_1BaseTest.shtml</filename>
    <member kind="function">
      <type></type>
      <name>BaseTest</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a73d91ead1486f1a99b4168984cbeb7db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BaseTest</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a9411a0151d3e65ee72cf4f3d8049c3b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>test</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>ad5f464c4c9e90358b6ea5dfaac4669c3</anchor>
      <arglist>(bool t)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>testEqual</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a37be8876e97338f1ae8c59c828e0716a</anchor>
      <arglist>(double a, double b)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>runAll</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a72e1d06c33208566b283be002a5851ef</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a1cf08c87a53877c36779b76a8c7bdc51</anchor>
      <arglist>(std::ostream &amp;) const =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testStart</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a30edf83a1ade48076ade8249ffc44aa3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>summaryString</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a0af2edfd9a437f166bceac07c8f9f58f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nSuccess_</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>ac5d2b28c96f4583c7fe57cb4a482abdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nError_</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>ab1e0cca7ba6ff2f33796a908870efa7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nExecutedTests_</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a82ebf00accc00a0dd8486b9c185a3942</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classI4H_1_1BaseTest.shtml</anchorfile>
      <anchor>a783c50f8047b73dbbabb138ef3adeeaa</anchor>
      <arglist>(std::ostream &amp;os, const BaseTest &amp;derivedTest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>I4H::Statistics</name>
    <filename>classI4H_1_1Statistics.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>Components</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>abf652bb4eda5c5e9f82affed241c806c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Statistics</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a60ddd90a571ed4c3ce8c0f6317a36d63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Statistics</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>ab68ede75479e44d5c35b78ec1284065b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a4faa80fa024777d57b6fa4b3559eec0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addVal</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a9fbd79a1963863cb3e82d988f8599eae</anchor>
      <arglist>(double val)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>mean</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a58fe596a167cdc0c8e0b5750ada86ab1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>max</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>aaf77d6d411059c2fa05431fcfaafa0ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>min</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a638d25e557181c60d9a38e0a50f0ec40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>nVals</name>
      <anchorfile>classI4H_1_1Statistics.shtml</anchorfile>
      <anchor>a51403e0d5bf9b618adf9436c037655bc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>I4H::TestStatistics</name>
    <filename>classI4H_1_1TestStatistics.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestStatistics</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>a7cc3873cc3d262126646f667b7ff5f4d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestStatistics</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>a0de0e2ebeea20c952da45b2a4186353d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNsuccess</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>acd283f3edbcf2d1829fcce207d209763</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNerror</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>a90a0af9e9bfdd3bdcc3ee82b021fc254</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>a097add5e14f84628453a80577f33c2b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMean</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>ab9e9c740cbf3cd51d7526e5c834eee2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classI4H_1_1TestStatistics.shtml</anchorfile>
      <anchor>aaf35c53fd3a94b705c007ed3860ff34a</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>sdo</name>
    <filename>namespacesdo.shtml</filename>
    <class kind="class">sdo::ReaderVOP</class>
  </compound>
  <compound kind="class">
    <name>sdo::ReaderVOP</name>
    <filename>classsdo_1_1ReaderVOP.shtml</filename>
    <member kind="function">
      <type></type>
      <name>ReaderVOP</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>ac242686f871ce90fca27e421ab30424b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ReaderVOP</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a1fed658731e6297475fe68e450a1c15a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_READERFREE</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a3a7d2bc8f197e4c79076cdf19ee3db03</anchor>
      <arglist>(scip_free)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_READERREAD</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a47aa6d3acc6e59e715391c1b81550360</anchor>
      <arglist>(scip_read)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_READERWRITE</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>ab179932444111924a92ec4fb3657c64f</anchor>
      <arglist>(scip_write)</arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>discretization</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>aaba028e08d42f95c95858b3e3d049666</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>lookuptype</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>afa714ecdd8338986a5b2e1060c78e64a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>positiveStates</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a2dee6aee3e5802ac017d9bde03e05b3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>simplify</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>aa573888edd875c61c6106c9a450bc4c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>useMinVariableFormulation</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a2395c1847f80dc2dd98cefd38f6c132d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>isolatelookups</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a47af3cf29a121a1009b7b7d1d7cc087d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Bool</type>
      <name>ratealgebraic</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a374f5043f51208e25465a4e9becffc0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>multistep</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>ab2343684144fd99857d31f105ee0e743</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nsinglesteps</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>aa72e542cdff1c235470a7aeca19768f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>lookupMaxRelErr</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>ac933519568c89a674a8ab6c198c8050c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>lookupAproxTol</name>
      <anchorfile>classsdo_1_1ReaderVOP.shtml</anchorfile>
      <anchor>a2dc8cd44b4f5d5b96f943da6b62f2e8a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>sdscip</name>
    <filename>namespacesdscip.shtml</filename>
    <class kind="class">sdscip::BranchruleControlFirst</class>
    <class kind="class">sdscip::ConstRateEvaluator</class>
    <class kind="class">sdscip::CopyablePointer</class>
    <class kind="struct">sdscip::EstimationData</class>
    <class kind="class">sdscip::EstimatorTestData</class>
    <class kind="class">sdscip::EstimatorTypeTestData</class>
    <class kind="class">sdscip::HeurSimODE</class>
    <class kind="class">sdscip::HyperCube</class>
    <class kind="class">sdscip::HyperPlane</class>
    <class kind="class">sdscip::IntervalODEintegrator</class>
    <class kind="class">sdscip::Line</class>
    <class kind="class">sdscip::ODEintegrator</class>
    <class kind="class">sdscip::Orthant</class>
    <class kind="class">sdscip::OrthantList</class>
    <class kind="class">sdscip::Point</class>
    <class kind="class">sdscip::PointODEintegrator</class>
    <class kind="class">sdscip::PointRateEvaluator</class>
    <class kind="class">sdscip::ProbDataCtrl</class>
    <class kind="class">sdscip::PropCtrlOBBT</class>
    <class kind="class">sdscip::PropOBRA</class>
    <class kind="class">sdscip::PropODE</class>
    <class kind="class">sdscip::PropProbingObjTest</class>
    <class kind="class">sdscip::ReduceODEintegrator</class>
    <class kind="class">sdscip::SBrateEvaluator</class>
    <class kind="class">sdscip::SDproblemStructure</class>
    <class kind="class">sdscip::SDproblemStructureExtendedInterface</class>
    <class kind="class">sdscip::SDproblemStructureFactory</class>
    <class kind="class">sdscip::SDproblemStructureInterface</class>
    <class kind="class">sdscip::SDproblemStructureV1</class>
    <class kind="class">sdscip::SDSCIPtest</class>
    <class kind="class">sdscip::SDVarBasic</class>
    <class kind="class">sdscip::SimRateEvaluator</class>
    <class kind="struct">sdscip::Statistics</class>
    <class kind="class">sdscip::TestBoundMap</class>
    <class kind="class">sdscip::TestEstimatorTypes</class>
    <class kind="class">sdscip::TestExprPiecewiseLinear</class>
    <class kind="class">sdscip::TestGeom</class>
    <class kind="class">sdscip::TestODEintegrator</class>
    <class kind="class">sdscip::TestSBrateEvaluator</class>
    <class kind="class">sdscip::TestSDplugin</class>
    <class kind="class">sdscip::Vector</class>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a1d12301bdd4ec036a5d18a71a80913dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a912bc46871c3a24d837e9933224a466c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a830c0cc2a0d855492067dd906ffe3ec3</anchor>
      <arglist>(std::ostream &amp;Str, CopyablePointer&lt; T &gt; const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a1b263dd419e5a3ca20368a3ff2697ea4</anchor>
      <arglist>(CopyablePointer&lt; T &gt; &amp;lhs, CopyablePointer&lt; T &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator+</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>af0699c79435db7f608964ab825b2ffd4</anchor>
      <arglist>(Vector lhs, Vector const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator-</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a2a750282191154a49bc6e2183f3db406</anchor>
      <arglist>(Vector lhs, Vector const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a67240dccd723d3114fee7565d246cefd</anchor>
      <arglist>(Vector lhs, double rhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>ae1031e1f5df40bb2d0421e7a8033b4ad</anchor>
      <arglist>(double lhs, Vector rhs)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator*</name>
      <anchorfile>namespacesdscip.shtml</anchorfile>
      <anchor>a35bec1971c45e7d6b1359586ac20afd8</anchor>
      <arglist>(Vector lhs, Vector rhs)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::BranchruleControlFirst</name>
    <filename>classsdscip_1_1BranchruleControlFirst.shtml</filename>
    <member kind="function">
      <type></type>
      <name>BranchruleControlFirst</name>
      <anchorfile>classsdscip_1_1BranchruleControlFirst.shtml</anchorfile>
      <anchor>a1b4f68f8a178ce8ee56f3acdf91ee22b</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BranchruleControlFirst</name>
      <anchorfile>classsdscip_1_1BranchruleControlFirst.shtml</anchorfile>
      <anchor>ac4f5de64cc6bda228698383214c4d53c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_BRANCHEXECPS</name>
      <anchorfile>classsdscip_1_1BranchruleControlFirst.shtml</anchorfile>
      <anchor>ae40b68aeff041914373bfe531b785411</anchor>
      <arglist>(scip_execps)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_BRANCHEXECLP</name>
      <anchorfile>classsdscip_1_1BranchruleControlFirst.shtml</anchorfile>
      <anchor>a4b5ad7a0519967bca6520f706fc2643f</anchor>
      <arglist>(scip_execlp)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_BRANCHEXECEXT</name>
      <anchorfile>classsdscip_1_1BranchruleControlFirst.shtml</anchorfile>
      <anchor>aaacbe704de1e62d19c550a47d2b856bf</anchor>
      <arglist>(scip_execext)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::ConstRateEvaluator</name>
    <filename>classsdscip_1_1ConstRateEvaluator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>ConstRateEvaluator</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a2c698ecf2c49aa2b9a7fa0880d430e84</anchor>
      <arglist>(int _nStates, SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ConstRateEvaluator</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>aeab5d3b9aa67fd3082b5de59089e051b</anchor>
      <arglist>(int _nStates, int _nAlgebraic, int _nControls, SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ConstRateEvaluator</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a510e27e5dd759a6cea47919bf79ede79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdots</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a105438243cd92e543a39b6f29ea57721</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; xDot)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR *</type>
      <name>getXdot</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>ab88a9163adae5562292f67e8a33bfce5</anchor>
      <arglist>(int nDim)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a63acb7e6a274266e4b481c05f30ec362</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PointRateEvaluator *</type>
      <name>clone</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a3a6da03a38d97c56ec7745d990a9e0bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>a66e57a276452862599417fe43b8323fa</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1ConstRateEvaluator.shtml</anchorfile>
      <anchor>af56399967c986fe8bfbd8dadf8fc12a2</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states, SCIP_Real *params)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PointRateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>aebd2d36bccc9eb75fb118401d59202a6</anchor>
      <arglist>(int _nStates, SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PointRateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a0ecbe8f536be5d1b21ebe9fb67c5f46c</anchor>
      <arglist>(int _nStates, int _nAlgebraic, SCIP *_scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PointRateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>ad1fab7f9347d02125f21a20e3db4e58f</anchor>
      <arglist>(int _nStates, int _nAlgebraic, int _nControls, SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PointRateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a6d9c4f8827d55f5498ad5ba2bf5ed84f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdot</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a201cd8c9eb49fe5d2545d22464fa57f8</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; &amp;xDot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdot</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a2e964e40215521fbb109769eb84a2524</anchor>
      <arglist>(SCIP_EXPR **xDot)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR *</type>
      <name>getXdot</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a7bc0bcb8b4254f48b73b1ee95f969fee</anchor>
      <arglist>(int nDim)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeAlgebraic</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a73589be764da61992c42f2415aaf4c89</anchor>
      <arglist>(std::vector&lt; SCIP_Real &gt; &amp;varValues, SCIP_Real *startParams)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printXdot</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>af970f1f00eca2bed836123e36cd76573</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>af9a9c33d45ec4d9d18b30af5a58186b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a92c49c0b200a2ecc402bb3e8cdf6a9b3</anchor>
      <arglist>(SCIP_EXPR **xDot)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR *</type>
      <name>getXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a157d0d0c84168999fb0c38d71deda29a</anchor>
      <arglist>(int nDim)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>POINT_RATE_EVALUATOR_TYPE</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a2c72f8db2bbfbc04ef4129d9d76d3459</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>RATE_EVALUATOR_CONST</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a2c72f8db2bbfbc04ef4129d9d76d3459ab7ce301fbae6b7d2e483459fa339c754</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>RATE_EVALUATOR_SIM</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a2c72f8db2bbfbc04ef4129d9d76d3459a2a20563410784782cdaf539b6bd94c1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nStates_</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>aedfb58945ca734a7ce51ca2b1371f8eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nAlgebraic_</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>ab653a915be7a33e61909ff1eeeda0662</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nControls_</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>af8ff70301f03c5b66c0b453da664e251</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::CopyablePointer</name>
    <filename>classsdscip_1_1CopyablePointer.shtml</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>CopyablePointer</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a2c744d6ae42513c6c68c019589186d95</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CopyablePointer</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>ab948cf377a64bf259e12f14c0ceb6bb6</anchor>
      <arglist>(T *_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CopyablePointer</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a171203776f1af0935ff19c1d09a934f7</anchor>
      <arglist>(CopyablePointer const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CopyablePointer</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a475524d6f87f09f638a287af538df563</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>CopyablePointer &amp;</type>
      <name>operator=</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>ab0b6e1a3f2c3e192dea01f2372a2848a</anchor>
      <arglist>(CopyablePointer rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>ad288b634f211e0bcd2ce85f7bf0a92c9</anchor>
      <arglist>(CopyablePointer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CopyablePointer</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>af37c2705c6b3f59c49438ff095817553</anchor>
      <arglist>(CopyablePointer &amp;&amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator*</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a13b0506c7d2f1ea6cafbd30e32656320</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>operator-&gt;</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a09a814995e15114539cf57cffc966ef9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator std::string</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>af2c6468dd502a93c912d857d9976e2ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>address</name>
      <anchorfile>classsdscip_1_1CopyablePointer.shtml</anchorfile>
      <anchor>a2e49f893c7d9a593ce87c9e5c2edcf37</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>sdscip::EstimationData</name>
    <filename>structsdscip_1_1EstimationData.shtml</filename>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>coefficient</name>
      <anchorfile>structsdscip_1_1EstimationData.shtml</anchorfile>
      <anchor>a606668f51e003efe1a746b6eadaa4bc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>constant</name>
      <anchorfile>structsdscip_1_1EstimationData.shtml</anchorfile>
      <anchor>a5f46734d4c684ee3b8bfbe99b9154df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>overestimate</name>
      <anchorfile>structsdscip_1_1EstimationData.shtml</anchorfile>
      <anchor>adca63b7f0bd38feea6c3e6b5674a104b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::EstimatorTestData</name>
    <filename>classsdscip_1_1EstimatorTestData.shtml</filename>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>a60043c7b9ef5cbd610a8dfbb1321cfbf</anchor>
      <arglist>(int boundidx)</arglist>
    </member>
    <member kind="variable">
      <type>std::pair&lt; std::vector&lt; SCIP_Real &gt;, std::vector&lt; SCIP_Real &gt; &gt;</type>
      <name>points</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>ac81425723f9caa770eb10859475a20f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::pair&lt; SCIP_Real, SCIP_Real &gt; &gt;</type>
      <name>argbounds</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>a23c1b783b6ab1ad799175b140ebbae9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>argvals</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>aa09f7a515317b1fdc3e33c3c6ee56dbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>label</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>ab28ccafaf1d4f2bcbc7305c4831e9aa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>overestimate</name>
      <anchorfile>classsdscip_1_1EstimatorTestData.shtml</anchorfile>
      <anchor>aaf630c7c1bd1584a0a38b90571c66ab1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::EstimatorTypeTestData</name>
    <filename>classsdscip_1_1EstimatorTypeTestData.shtml</filename>
    <member kind="function">
      <type></type>
      <name>EstimatorTypeTestData</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>a24eb6ef108a7fa420af941694b4a42e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SAFE_ESTIMATOR &gt;</type>
      <name>validTypes</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>abf6d4fcf65022f6488357a07ed83d19d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SAFE_ESTIMATOR &gt;</type>
      <name>bestTypes</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>aab827c3b88165eaaa50b6928ec1e2323</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>x1</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>a50021281e34e9471e46595d8ab5f8b66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>x2</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>a38beeb82ffebf09fd424346c7d6294ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>e5valid</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>ad0bedd6de39e6554f87654e7f5968c2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>e6valid</name>
      <anchorfile>classsdscip_1_1EstimatorTypeTestData.shtml</anchorfile>
      <anchor>a9c38eafc24d63df6b492ddf862c409d4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::HeurSimODE</name>
    <filename>classsdscip_1_1HeurSimODE.shtml</filename>
    <member kind="typedef">
      <type>ReduceODEintegrator::REDUCTION_MODE</type>
      <name>REDUCTION_MODE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>ab84f1e8e9e796943b4188c95d055960a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>ad893a72c4ab5f068af94e9e00970b9b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>a636e957c01cf1cc70021496dcfd360b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HeurSimODE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>ad9a3e434c1b5309db304cf1a596f763d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~HeurSimODE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>a7594e924e40fe08e4327c277d42b6be6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEURFREE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>af791d48117b5c1147b9e73728fd52e9e</anchor>
      <arglist>(scip_free)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEURINIT</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>afc3f8c03be0564e11cdd44f4b4b664ed</anchor>
      <arglist>(scip_init)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEUREXIT</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>af80a4ec73b6c6f315ee9e8c5023fb508</anchor>
      <arglist>(scip_exit)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEURINITSOL</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>ac4f780ef21afd2281e40f2276675e6a7</anchor>
      <arglist>(scip_initsol)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEUREXITSOL</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>a1c999e9d4c50b83bb1faa141e489704a</anchor>
      <arglist>(scip_exitsol)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEUREXEC</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>a197f3cc59b3b342896a5416a6a029dbb</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEURCLONE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>adb4b53c21baba91bffc5111d1a02503e</anchor>
      <arglist>(ObjCloneable *clone)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_HEURISCLONEABLE</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>ae246bc739d5ddba1fa8cac89ce6c7bba</anchor>
      <arglist>(iscloneable)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ncalls_</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>aff54b559c7a9020539a56e72d7d3600f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP_SOL *</type>
      <name>sol_</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>aa3c5e179f9d9fc686e14b3d0e8a5ef19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>timesCalled_</name>
      <anchorfile>classsdscip_1_1HeurSimODE.shtml</anchorfile>
      <anchor>aa52e9452332d61dda06a97261bd20774</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::HyperCube</name>
    <filename>classsdscip_1_1HyperCube.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; double, double &gt; &gt;</type>
      <name>Extent</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ab67bdc83b5076051a5647cf5413b97ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; double, double &gt; &gt;::iterator</type>
      <name>ExtentIterator</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a837c7a35d1b50f0cf8e78e1e4abad5fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; double, double &gt; &gt;::const_iterator</type>
      <name>ConstExtentIterator</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ac69fed1ab147c5c6c4c4f99b970b8e22</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; sdscip::Orthant, std::vector&lt; sdscip::Vector &gt; &gt;</type>
      <name>VertexIntersectionsPair</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>af4d9172e991d767fc0c4f9d6e852f6ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperCube</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a32cbff1fc892dc4924ceac0e1fd15595</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperCube</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a9983959f237f987daf6844683be5465d</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~HyperCube</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aa88e2236d16cea52757d4c8dc21e2eef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aba063d13e119b27c5085a7f31cc9fa21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addDim</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aa39481ae0012840c80e5ab568877df9c</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function">
      <type>Extent::iterator</type>
      <name>beginIt</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a82d88bacac19cca8bb812c914c47e4a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Extent::iterator</type>
      <name>endIt</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a74550b42bb5dba49bce54eed822599a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ConstExtentIterator</type>
      <name>constBeginIt</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aa55a35c4bc1cb29eeb6e2c9dea385912</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ConstExtentIterator</type>
      <name>constEndIt</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a8fcefcecfa603cb98475eaf91e048091</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getLowerExtent</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>af9488ac1fa0fee80f2ba71cc9f4bf5a0</anchor>
      <arglist>(int dim) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getHigherExtent</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a34310ac79dada888dc3eab907826bc26</anchor>
      <arglist>(int dim) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getExtent</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a2e1e2b295eae39319c45248a1788f2b2</anchor>
      <arglist>(int dim) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>areExtentsFinite</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a268e7201f6a5c0340db13a102cf7c875</anchor>
      <arglist>(SCIP *scip) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getNormalizationFactor</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aa45f3a2c4898cb65c4155d5b9a3b3180</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a04501299b86a86f06f57530d77cca3d3</anchor>
      <arglist>(sdscip::Vector vec)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a6d91a14490d4d7a2b42e6eecb0162a6d</anchor>
      <arglist>(SCIP *scip, sdscip::Vector vec)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isOnFace</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>af17d93d9469d0a679df32abe5866640c</anchor>
      <arglist>(SCIP *scip, sdscip::Vector vec)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isOnVertex</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ad1972989da0912dbcc6fccaca927a025</anchor>
      <arglist>(SCIP *scip, sdscip::Vector vec)</arglist>
    </member>
    <member kind="function">
      <type>VertexIntersectionsPair</type>
      <name>findSeveredVertex</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a99cb1db278fe610683a47a0f00783433</anchor>
      <arglist>(const sdscip::HyperPlane *plane) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getSeparatedVolume</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>a3b9154a09402b5a94566f353646bbdc3</anchor>
      <arglist>(const sdscip::HyperPlane *plane) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getRelativeSeparatedVolume</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ab10919f642c483b6c812ec8dc38102be</anchor>
      <arglist>(const sdscip::HyperPlane *plane) const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getVolume</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ad341b2150f14a7bf51f929f96b35d1df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>sdscip::Vector</type>
      <name>getVertex</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>aa5ce136be0c36071ccd99227f07765a1</anchor>
      <arglist>(sdscip::Orthant orth) const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; sdscip::Line &gt;</type>
      <name>getEdges</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ae7246452fd65534ea576d890916006f3</anchor>
      <arglist>(sdscip::Orthant orth) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>intersects</name>
      <anchorfile>classsdscip_1_1HyperCube.shtml</anchorfile>
      <anchor>ae1999f0ec601f7c8b2f0193b75a50cc0</anchor>
      <arglist>(const sdscip::HyperPlane plane) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::HyperPlane</name>
    <filename>classsdscip_1_1HyperPlane.shtml</filename>
    <member kind="typedef">
      <type>Vector::Components::iterator</type>
      <name>ComponentIterator</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>af0fbe26037429e5fdd0ab806025c631c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperPlane</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>a5541bee4ff531b3062a0c0b49ea15bf8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperPlane</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>aad71e4e8619b863b6da976e759735270</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperPlane</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>a1e81ce7ac65cc6cb45b5fae7aaa7de5d</anchor>
      <arglist>(sdscip::Vector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HyperPlane</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>ac44734994bd14adf56ee0da682140956</anchor>
      <arglist>(Vector _vector, Vector _point)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~HyperPlane</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>a0613ee9dbdebf787e77b6c3508fe0c88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>ab67311f3b9cc3689c7f9d2ee9860d95a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addDim</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>a169201501eea4aa5d271f02f364174e3</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getDim</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>afc04d998da2acc77f547b4faf26b0e3a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const sdscip::Vector *</type>
      <name>getVector</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>abb0010935d2dcd580d9c2f1ef2203be1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const sdscip::Vector *</type>
      <name>getPoint</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>ac7e3dc757c202781a9389812bc432988</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Vector::Components::iterator</type>
      <name>vecBeginIt</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>ab7b20cc8b40547a127deb04b0e803e7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector::Components::iterator</type>
      <name>vecEndIt</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>afa81acfe279bf0577a524112ca97a7bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector::Components::iterator</type>
      <name>pointBeginIt</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>aa779bb9550a336ce5e02a418ff4d67d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector::Components::iterator</type>
      <name>pointEndIt</name>
      <anchorfile>classsdscip_1_1HyperPlane.shtml</anchorfile>
      <anchor>ad2ea3a0b3899c0b24ac272cb99cf8ed0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::IntervalODEintegrator</name>
    <filename>classsdscip_1_1IntervalODEintegrator.shtml</filename>
    <member kind="enumeration">
      <type></type>
      <name>INTERVAL_INTEGRATOR_CONTROL_MODE</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a576118b784127898f9c078dc8468cdf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CONTROL_MODE_SINGLE_INTERVAL</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a576118b784127898f9c078dc8468cdf1ae8a259946f9abe463b5a1f92ffb26d3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CONTROL_MODE_STARTMIDEND</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a576118b784127898f9c078dc8468cdf1abc8f1ab8e1ce27c70842269bf4e5d8be</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructure::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ad03203ebfdf7718ef99d4b73b908d7dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructure::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a5a53abad786875d55e40241944aacefe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntervalODEintegrator</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>aafb49135dc5754bde26588ac43a7aa8e</anchor>
      <arglist>(SCIP *_scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IntervalODEintegrator</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a65caab0e66367457f7096a5351d266df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SBrateEvaluator *</type>
      <name>rateEvaluator</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a1228bbfe9454c1136b80e34c331c34c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Interval</type>
      <name>getState</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ac1b824cb4d5b80d95a6dd1fee588835f</anchor>
      <arglist>(int dim)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getStates</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>adbfd5ca08d324393e11b0f7641ba06db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getState</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a04591dfa05fa5a3ad38e0ac28ddfbdbe</anchor>
      <arglist>(int dim, SCIP_BOUNDTYPE bndtype)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getControls</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ac17cbd04cde9612723647da7f9c9ed7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ac366499444ab7843f32cddec2825b78e</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Interval &gt; states, std::vector&lt; SCIP_Interval &gt; controls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a9225b8132886d38bbe3739a7612b5997</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Interval &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControl</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a331ae2cd2dca432e088523c12c699878</anchor>
      <arglist>(int controlId, SCIP_Real inf, SCIP_Real sup)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControls</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ae619854571055b6c8937c3ecaf071d88</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;controls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEndControls</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a57d3aa35af7d15b943840d6326582156</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;endControls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cycleControls</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a3c90bed610023a42a7c06ecc1966c539</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getNewX</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a9b8ea17fc79596ebe221b3b42031a784</anchor>
      <arglist>(const std::vector&lt; std::vector&lt; SCIP_Interval &gt; &gt; &amp;kMatrix, const std::vector&lt; double &gt; &amp;row, int s, SCIP_Real c)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a767d63f0d734c3bf5bdbf87bcbfda8c6</anchor>
      <arglist>(SCIP_Real *params=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a2dc36c2fb11d01cd7101f2e80f3e8dfe</anchor>
      <arglist>(const BoundMap &amp;stateBounds, SCIP_Real *params=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a428983f8d1c6ad346292498533566786</anchor>
      <arglist>(const BoundMap &amp;startStateBounds, const BoundMap &amp;endStateBounds, SCIP_Real *params=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a6501a54dd8ae76af5e3c1d7fc757d29a</anchor>
      <arglist>(const BoundMap &amp;startStateBounds, const BoundMap &amp;midStateBounds, const BoundMap &amp;endStateBounds, SCIP_Real *params=NULL)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>isDiverging</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ad35ccfd867bd4096db5e87c2f77125e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>checkBounds</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a48e46e33f080c0a5d53edab320d9dd51</anchor>
      <arglist>(const BoundMap &amp;bounds) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a323fbf16123f3d4480ba35e2ef361541</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>statesToString</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a193f3e2fcb70ae96b06a7267aba01021</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeStates</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a8882cf277302d99d88ef82521ad33118</anchor>
      <arglist>(std::ofstream &amp;outFile)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>controlsToString</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a7c1a42f8e9439f8c180953d0899521ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControlMode</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a0a0176f9f34a03bc8ed2927e86299033</anchor>
      <arglist>(INTERVAL_INTEGRATOR_CONTROL_MODE mode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdots</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a568c6d8c6b4218604aaa791b855e1774</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; &amp;xDot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdot</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>ad544b22191ef4c4f1c379b9058dc7487</anchor>
      <arglist>(SCIP_EXPR **xDot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printXdot</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>aeb6bbb80cfc896a8eb26859dca7b30b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>sane</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a099ea88afd6762ee1cf3053c9b09c020</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ODEintegrator</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a77e2cd1af34818bac93e5d2a8564aba0</anchor>
      <arglist>(SCIP *_scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ODEintegrator</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>ac29625f94b08b46d28459f7bd63819d3</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdots</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>ad90a81638a89163b18125ae50198fdf2</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; xDot)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getT</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a4df094c794e2e041fe8dcbc2e82aed3f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP *</type>
      <name>getScip</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a1df0bfa8e188a4c1ead101112818f6cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printVec</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a4f236cab0c4864449af114eb342a8b2c</anchor>
      <arglist>(std::vector&lt; double &gt; vec, std::string message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printXdot</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a18736546c8b06cf98d3e3b7771bb4dd8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNStates</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a101387595420cc734a06257dbc12d673</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNControls</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>aa211802503f6ad37641b9861f0a86228</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNAlgebraic</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a082c80f4d86a15520fd4a83ce63dac06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNStates</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a415b501d849ca7feeae2460304f94e66</anchor>
      <arglist>(int states)</arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>saneBoundGap_</name>
      <anchorfile>classsdscip_1_1IntervalODEintegrator.shtml</anchorfile>
      <anchor>a0d9e770780c89d7be4628c828c2126cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SCIP *</type>
      <name>scip_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a8191b8f862c3175bfbad2f79697ae19a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nStates_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a671e4fd9feec58ced3084f4c17cbad01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nControls_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a7b978b035c600c17b7e8d43a7e6fd12d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nAlgebraic_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a1ab412b95472bcb2b744b3711cbfd422</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SCIP_Real</type>
      <name>dt_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>aa66407110e6ecb398ef5946cb68a8ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>nIntermediateSteps_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a62b857c095eda446e3c8e88e8bc27598</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SCIP_Real</type>
      <name>dtIntermediate_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a245a8e5bc309214064a192c5d73f5b55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SCIP_Real</type>
      <name>t_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a8170b46689cf0fb715a2bf1f38b306f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>discretization_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>adff0d73286679238e5e64a719de23eba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sdo::ButcherTableau</type>
      <name>tableau_</name>
      <anchorfile>classsdscip_1_1ODEintegrator.shtml</anchorfile>
      <anchor>a1ec46a14e53f52af3cee3b5a71302cb2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::Line</name>
    <filename>classsdscip_1_1Line.shtml</filename>
    <member kind="typedef">
      <type>sdscip::Vector::Components::iterator</type>
      <name>ComponentIterator</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>a140f58889fb8ccbed417fbd9fd58ebda</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Line</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>ac1c1bd7b0e18194d6ddd8cab44a5ad44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Line</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>a873b771b2b866016b0e737e2b1c841e3</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Line</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>ac905494a7679023fbf4b64f61cb11c01</anchor>
      <arglist>(sdscip::Vector a, sdscip::Vector b)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Line</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>a4923458f2ef78d84d841a7a62b76eeb1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>a7bc3e14c77f95ee8d4f6e4ba2ca6ed5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sdscip::Vector</type>
      <name>intersection</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>a7943260775d1f09c1c7ad21ce0ebfedc</anchor>
      <arglist>(const sdscip::HyperPlane *plane)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getDim</name>
      <anchorfile>classsdscip_1_1Line.shtml</anchorfile>
      <anchor>ac87f598f37ecdc88a4b2c2ca60e59e8c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::ODEintegrator</name>
    <filename>classsdscip_1_1ODEintegrator.shtml</filename>
  </compound>
  <compound kind="class">
    <name>sdscip::Orthant</name>
    <filename>classsdscip_1_1Orthant.shtml</filename>
    <member kind="typedef">
      <type>std::deque&lt; bool &gt;::iterator</type>
      <name>HalfSpaceIterator</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a5ede6b1ded842b80b4cbdd884a95b1ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; bool &gt;::const_iterator</type>
      <name>ConstHalfSpaceIterator</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a4b8c1cb727a6d454ef2805447cf6880f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Orthant</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a5dd1763e45f34b172a814f913073f10e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Orthant</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>af5bf72ddf1f0cc9c45efc42ad670a900</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Orthant</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ae830592457848591c7182cc5c06d8ae1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a54d10474942f923d51116e56357f4ede</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>HalfSpaceIterator</type>
      <name>beginIt</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a2a59289cb949415af34855416ac40d17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>HalfSpaceIterator</type>
      <name>endIt</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ada64d3490ba88ab24f8b8f62f5abd9c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ConstHalfSpaceIterator</type>
      <name>constBeginIt</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>aace57bc3ac178ea5fcac7958601471dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ConstHalfSpaceIterator</type>
      <name>constEndIt</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ac96e950cc203d52481c97b67ddae2560</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>HalfSpaceIterator</type>
      <name>lastIt</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a31fa3f731b87b4e6fdb8aa215df0efcb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setAll</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ae491af6f69d78f9d0c9225b02faa1bd0</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>addDimFront</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ae8ffd06ce4e7b408bb11ecffd729bf4c</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>toggleDimFront</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ac7fdbedc2633ab78842dfe30a7279c02</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getHalfSpace</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>a20f041fad643435cf82a873f39df51b1</anchor>
      <arglist>(int dim)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getDim</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>ab53b1c12f2c47e778a327e240a3282bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Orthant &gt;</type>
      <name>getAllOrthants</name>
      <anchorfile>classsdscip_1_1Orthant.shtml</anchorfile>
      <anchor>aed9ff02d3ce921fe19bfd90dffdab5e1</anchor>
      <arglist>(int ndim)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::OrthantList</name>
    <filename>classsdscip_1_1OrthantList.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; Orthant &gt;::iterator</type>
      <name>OrthantIterator</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>a55b1709e0542146d691f94aaca2c7076</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OrthantList</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>adc5b1e995ccfd2fc9d127a7d5e0897de</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OrthantList</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>af632878d4eff35927e7fcb8c093be1ed</anchor>
      <arglist>(int ndim)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~OrthantList</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>a887fb9b97ae2769e96a512cc952afc6c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeOrthants</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>ac8d5225f58ef56f83e35f81c16f71ea8</anchor>
      <arglist>(int ndim)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>ae3ae41e573527dfcbbfdc1514dac295d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Orthant &gt;::iterator</type>
      <name>beginIt</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>a08a0332a96db2380e0aff96eae687657</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Orthant &gt;::iterator</type>
      <name>endIt</name>
      <anchorfile>classsdscip_1_1OrthantList.shtml</anchorfile>
      <anchor>a033f282ae7dca95b6f9766bc810eff41</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::Point</name>
    <filename>classsdscip_1_1Point.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>Components</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>ad37f7bf3eeab58d9d297966fcee07acb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a307adc634e5574815281a237f42d73fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>ae6262b1ab34d18ccbd8d8c5858230aa3</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a001b45da986f22c3797fc72db1d8c1a7</anchor>
      <arglist>(std::vector&lt; double &gt; components)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a12805ac6e4c1a16b99783453f57119c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>aa4561e6247b6ea52ac62111ab764b252</anchor>
      <arglist>(double x1, double x2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a9d52aac86b12726ce97fe10d20453108</anchor>
      <arglist>(double x1, double x2, double x3)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>ab9b2e893e74a7facb02dc3c8cc03193c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addDim</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a9e6b74a61e5251d08caf8a07bbd6d414</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="function">
      <type>Components::iterator</type>
      <name>beginIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>aece784cc16dd021c6f387f304e17f73b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Components::iterator</type>
      <name>endIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a342790d6cc27fd19edb9405db2269c6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Components::iterator</type>
      <name>lastIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>aa1812f9f5df5c7386c09eb3e70e8664e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point::Components::const_iterator</type>
      <name>constBeginIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a383b44dcba83936b94864eeb862d7087</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Point::Components::const_iterator</type>
      <name>constEndIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a96ede5afa55ca742086ca4a52a06a173</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Point::Components::const_iterator</type>
      <name>constLastIt</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a7dca2607fc05e8af8214632dae533f98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getDim</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>ac7d87aadf13de47b479299cf20d89b01</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComponent</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>adf086b7312b15d95f5318b804d787fd5</anchor>
      <arglist>(int dim, double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getComponent</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a5dd70c9a373d13ec2fd56fc5cab0cd45</anchor>
      <arglist>(int dim) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>ndim_</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>afb0b6e96c54d546649ea64e7976a35b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Components</type>
      <name>components_</name>
      <anchorfile>classsdscip_1_1Point.shtml</anchorfile>
      <anchor>a3ee2890e1705683991cd6209f8883b72</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PointODEintegrator</name>
    <filename>classsdscip_1_1PointODEintegrator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PointODEintegrator</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a28ff83dda2b7187514b6e88d20195604</anchor>
      <arglist>(SCIP *_scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls, PointRateEvaluator::POINT_RATE_EVALUATOR_TYPE _rateEvalType)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PointODEintegrator</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a584984657fb6585850e43b37006e2b5c</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>CopyablePointer&lt; PointRateEvaluator &gt;</type>
      <name>rateEvaluator</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a993fc05ed79001db8ff83e90d65437a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getStates</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a2c68487f7fded9d934e31e2562c4d5b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getControls</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a5395149caddfbff726083c4b4e7a9f87</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getState</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>af0c29bceed80f05d1e9eb8833918fefd</anchor>
      <arglist>(int dim)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getAlgebraic</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>af3ebaacdf722f7e42b15b5c23e55f0fb</anchor>
      <arglist>(int varId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getControl</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a77b0742a19ef969acb9bbc691b30ce4c</anchor>
      <arglist>(int varId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a189b2305e075ad21726d7f649e437c33</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a28be66e12e228572f4a129c075b37823</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states, std::vector&lt; SCIP_Real &gt; controls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a0153271d3d5af72970c92e66680e1ecc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>step</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a3602a5934efc2e81811bf9bc25606187</anchor>
      <arglist>(SCIP_Real *startParams, SCIP_Real *endParams)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>acca8659981a1507043328954a6ab03e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>statesToString</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a148c0625fb6878fecbef621e1d723a94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>algebraicToString</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a5a28a4d242111f7fc05b21a38ba8c05e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeStates</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a900884a6eb4eb8ad44325ff2c7dd82c3</anchor>
      <arglist>(std::ofstream &amp;outFile)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>controlsToString</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a9798e59e83a9be7e6c6c785620d01189</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdots</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>ae6c64aba4601589b99fa814318ddcd60</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; &amp;xDot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdots</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a2cfd41e3e0ca72a9da0173c4739e7807</anchor>
      <arglist>(SCIP_EXPR **xDot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>a63281f2487867fe98172500ca748e3ae</anchor>
      <arglist>(SCIP_EXPR **algebraicExpressions)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printXdot</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>aef8f7ea28810dbab749015eba453ce26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeAlgebraic</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>ade367a4c0f89b262c1e063bc0a7154a6</anchor>
      <arglist>(SCIP_Real *params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControls</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>aefd69a5e3ce086613109409a7ac1a387</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;controls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEndControls</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>acf0b4342d517a0e37c4539f3b1587994</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;endControls)</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>ReduceODEintegrator</name>
      <anchorfile>classsdscip_1_1PointODEintegrator.shtml</anchorfile>
      <anchor>aed7b7134eba4547e9e898da76c586cc0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PointRateEvaluator</name>
    <filename>classsdscip_1_1PointRateEvaluator.shtml</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getName</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a66940ded3b366e246f3d2e71aaaf4b9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual PointRateEvaluator *</type>
      <name>clone</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a89e5f4a5f5566a4d776a67727869a6a7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>aed91c851e476e4c008d415b3ac609148</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; varValues)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a29384cf186e90fc9b1e9d482c41f8afd</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; varValues, SCIP_Real *params)=0</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>SBrateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>a98183a4244d68b32654d35481fecea2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>SimRateEvaluator</name>
      <anchorfile>classsdscip_1_1PointRateEvaluator.shtml</anchorfile>
      <anchor>aa2e2af971329b5251f7c904121581ab2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::ProbDataCtrl</name>
    <filename>classsdscip_1_1ProbDataCtrl.shtml</filename>
    <member kind="function">
      <type></type>
      <name>ProbDataCtrl</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>adbf187fc64052f38030e09a05c4dddc8</anchor>
      <arglist>(GRAPH *g)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ProbDataCtrl</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>a6a4d5468b0bea457b80182e51b50b08d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_RETCODE</type>
      <name>scip_copy</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>ad76592b7aa09040eec9bbed9dbc4b10a</anchor>
      <arglist>(SCIP *scip, SCIP *sourcescip, SCIP_HASHMAP *varmap, SCIP_HASHMAP *consmap, ObjProbData **objprobdata, SCIP_Bool global, SCIP_RESULT *result)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_RETCODE</type>
      <name>scip_delorig</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>af143b9553b78d9806147805a7c8f3e15</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_RETCODE</type>
      <name>scip_deltrans</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>a08a407c695f9a0242879f725d757d182</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_RETCODE</type>
      <name>scip_trans</name>
      <anchorfile>classsdscip_1_1ProbDataCtrl.shtml</anchorfile>
      <anchor>af3d8cb6a2554645952a8ee6560067470</anchor>
      <arglist>(SCIP *scip, ObjProbData **objprobdata, SCIP_Bool *deleteobject)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PropCtrlOBBT</name>
    <filename>classsdscip_1_1PropCtrlOBBT.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PropCtrlOBBT</name>
      <anchorfile>classsdscip_1_1PropCtrlOBBT.shtml</anchorfile>
      <anchor>a40c6c6b3d325217d7eae7fc529bdc556</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PropCtrlOBBT</name>
      <anchorfile>classsdscip_1_1PropCtrlOBBT.shtml</anchorfile>
      <anchor>ac0c2cffcdc8c54155b694c186be83fec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>classsdscip_1_1PropCtrlOBBT.shtml</anchorfile>
      <anchor>a80ebf96d2ab72f3216306257211cca52</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>applyObbt</name>
      <anchorfile>classsdscip_1_1PropCtrlOBBT.shtml</anchorfile>
      <anchor>a6972881bd72d8fd7142376197757b5c0</anchor>
      <arglist>(SCIP *scip, SCIP_PROPDATA *propdata, SCIP_Longint itlimit, SCIP_RESULT *result)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>findNewBounds</name>
      <anchorfile>classsdscip_1_1PropCtrlOBBT.shtml</anchorfile>
      <anchor>a855917543bdd91e3cd8cd95e55ca92fe</anchor>
      <arglist>(SCIP *scip, SCIP_PROPDATA *propdata, SCIP_Longint itlimit)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PropOBRA</name>
    <filename>classsdscip_1_1PropOBRA.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PropOBRA</name>
      <anchorfile>classsdscip_1_1PropOBRA.shtml</anchorfile>
      <anchor>aedfb6d4bdd98149ab519625dffd5e707</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PropOBRA</name>
      <anchorfile>classsdscip_1_1PropOBRA.shtml</anchorfile>
      <anchor>a450b63c67719766ac5405708ea4c6bf6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPINIT</name>
      <anchorfile>classsdscip_1_1PropOBRA.shtml</anchorfile>
      <anchor>adbda641d59cc253d2455cbf0d37fde92</anchor>
      <arglist>(scip_init)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>classsdscip_1_1PropOBRA.shtml</anchorfile>
      <anchor>a58e6d4d16ab8cba4b940b6ed4711f1b7</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPPRESOL</name>
      <anchorfile>classsdscip_1_1PropOBRA.shtml</anchorfile>
      <anchor>add6b90f3d9acffebfb3f2a9d0e17f95c</anchor>
      <arglist>(scip_presol)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PropODE</name>
    <filename>classsdscip_1_1PropODE.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PropODE</name>
      <anchorfile>classsdscip_1_1PropODE.shtml</anchorfile>
      <anchor>aac69cc68d01ff67ef62f5d9802a6bed5</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PropODE</name>
      <anchorfile>classsdscip_1_1PropODE.shtml</anchorfile>
      <anchor>a81e799dc29c733e6c12fc0a266f4dcc1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPINIT</name>
      <anchorfile>classsdscip_1_1PropODE.shtml</anchorfile>
      <anchor>aeb77bf61b7ee47d9756d0f0944c14b41</anchor>
      <arglist>(scip_init)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>classsdscip_1_1PropODE.shtml</anchorfile>
      <anchor>a64c632b61ef5d5427bd67bc68e61d0f7</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPPRESOL</name>
      <anchorfile>classsdscip_1_1PropODE.shtml</anchorfile>
      <anchor>a7ebb57b5604c59761188364fd1b6d5fa</anchor>
      <arglist>(scip_presol)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::PropProbingObjTest</name>
    <filename>classsdscip_1_1PropProbingObjTest.shtml</filename>
    <member kind="function">
      <type></type>
      <name>PropProbingObjTest</name>
      <anchorfile>classsdscip_1_1PropProbingObjTest.shtml</anchorfile>
      <anchor>ac2e956e0678d16d9dea3817df2f5c440</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PropProbingObjTest</name>
      <anchorfile>classsdscip_1_1PropProbingObjTest.shtml</anchorfile>
      <anchor>ad611053a2e0ffdba02254d2db04475a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>SCIP_DECL_PROPEXEC</name>
      <anchorfile>classsdscip_1_1PropProbingObjTest.shtml</anchorfile>
      <anchor>a7d90309ae3a8aa3f98006418dabe0b00</anchor>
      <arglist>(scip_exec)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>applyObbt</name>
      <anchorfile>classsdscip_1_1PropProbingObjTest.shtml</anchorfile>
      <anchor>a7241ae90863c2f669c75ba32d63d1056</anchor>
      <arglist>(SCIP *scip, SCIP_PROPDATA *propdata, SCIP_Longint itlimit, SCIP_RESULT *result)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>findNewBounds</name>
      <anchorfile>classsdscip_1_1PropProbingObjTest.shtml</anchorfile>
      <anchor>a45fe9021559ad70397b3886b77587f9a</anchor>
      <arglist>(SCIP *scip, SCIP_PROPDATA *propdata, SCIP_Longint itlimit)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::ReduceODEintegrator</name>
    <filename>classsdscip_1_1ReduceODEintegrator.shtml</filename>
    <member kind="enumeration">
      <type></type>
      <name>REDUCTION_MODE</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a23bd24da70071e38a39f1d4a4a8e0940</anchor>
      <arglist></arglist>
      <enumvalue file="classsdscip_1_1ReduceODEintegrator.shtml" anchor="a23bd24da70071e38a39f1d4a4a8e0940a9a090bad798700b8bd51cb1608ba4d3f">REDUCTION_MODE_LOWER</enumvalue>
      <enumvalue file="classsdscip_1_1ReduceODEintegrator.shtml" anchor="a23bd24da70071e38a39f1d4a4a8e0940aa23c017a179a30d429920ea3763fa0c9">REDUCTION_MODE_UPPER</enumvalue>
      <enumvalue file="classsdscip_1_1ReduceODEintegrator.shtml" anchor="a23bd24da70071e38a39f1d4a4a8e0940a5672962672635197129d23a32a3e79d4">REDUCTION_MODE_MIDPOINT</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SOLVE_MODE</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>af8ad03f3c8ac697ed9e5dbaf03366f3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SOLVE_MODE_SIM</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>af8ad03f3c8ac697ed9e5dbaf03366f3bafefbd7286f786e034ce1c12cac80e1b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SOLVE_MODE_CONTROL</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>af8ad03f3c8ac697ed9e5dbaf03366f3ba8b7e66ab55909da222dfde6fb80daf04</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceODEintegrator</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>ab710ca4d249b05af7524ae0c624b2e7a</anchor>
      <arglist>(SCIP *_scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ReduceODEintegrator</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>aadb99f220ed00969d8faf11601f1c180</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>aeb01b0c3a486560a5a077a7a4fbe0abc</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a0a273e51bc4cc8aff41d892e094335b0</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states, std::vector&lt; SCIP_Real &gt; controls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitial</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>ae6469ac29e58439d3461aba4c1badfa5</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Interval &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEndControls</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a730a3c70b4e0161caf485b473ceb8cc9</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;endControls)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControls</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>ae230874d53d7165ba2105817068a9da2</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;controls)</arglist>
    </member>
    <member kind="function">
      <type>SOLVE_MODE</type>
      <name>getSolveMode</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a184732550160cfa4fc2350a3f02e33cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setReductionMode</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a3b567952753604470bc6f4dc375a4b72</anchor>
      <arglist>(REDUCTION_MODE mode)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a1290293e0dd6ad7e1c5e0883b0c95d30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getSolveModeString</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a933832d86a2a23ae0988acc838865376</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getReductionModeString</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a9ef1865d1b09fe32d02afd6d3dd7e653</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; REDUCTION_MODE &gt;</type>
      <name>getReductionModeVector</name>
      <anchorfile>classsdscip_1_1ReduceODEintegrator.shtml</anchorfile>
      <anchor>a15555fb072cf0ce4da6062bd03c9ed1f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SBrateEvaluator</name>
    <filename>classsdscip_1_1SBrateEvaluator.shtml</filename>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundKey</type>
      <name>BoundKey</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a743af0177a984c844b5a5f8eb90c3257</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SDproblemStructureInterface::BoundMap</type>
      <name>BoundMap</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a8679e758fd111c53f09fa3cb9151b8b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SBrateEvaluator</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a744e1f5f9b88293e4044854ed4b62189</anchor>
      <arglist>(int _nStates, SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SBrateEvaluator</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a7ef892e0f6a23db034f02d712696b56b</anchor>
      <arglist>(int _nStates, int _nAlgebraic, int _nControls, SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SBrateEvaluator</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a6584078a7327aa6dc77093709d9f93c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>af44c43ebce345b847616b1adfef9747b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PointRateEvaluator *</type>
      <name>clone</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a3fc9f90f50c5ed39f82d49de2a95f32c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a15dc23a4843d145c96d1fb76f10f5c45</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a914717d8bc62353644488babe7af16d2</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states, SCIP_Real *params)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>ae2b9551211a248613aadbfa25b5f5c51</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Interval &gt; &amp;varValues, const BoundMap &amp;stateBounds, SCIP_Real *params, SCIP_Real infinity)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getOmega</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a03417b3dc72292f487ebb81d5553eaf5</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE boundType, const std::vector&lt; SCIP_Interval &gt; &amp;varValues, const BoundMap &amp;stateBounds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeAlgebraic</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a249b1aadaa20c2b845de1b9ccd4b47a5</anchor>
      <arglist>(std::vector&lt; SCIP_Interval &gt; &amp;varValues, SCIP_Real *params, SCIP_Real infinity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyB</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>ae4aef2a2dbd80ae05f7b633ff3b3fbcf</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE boundType, std::vector&lt; SCIP_Interval &gt; &amp;varValues)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyEnclosure</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>aa63285c941cd4edf3b8309dbb9cde20c</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE boundType, const BoundMap &amp;stateBounds, std::vector&lt; SCIP_Interval &gt; &amp;varValues)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getStateBound</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>acf0776c429691aa56742aee4c9f87c1f</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE boundtype)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>hasStateBound</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a06699693a3a3da516eeba921411848c3</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE boundtype)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addGlobalStateBound</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>aa372745781cbf73435d7e846f926e684</anchor>
      <arglist>(int state, SCIP_BOUNDTYPE, SCIP_Real bound)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printGlobalStateBounds</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a653f45aaef90ca7a8ca550f9d961fb88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>TestSBrateEvaluator</name>
      <anchorfile>classsdscip_1_1SBrateEvaluator.shtml</anchorfile>
      <anchor>a2a24252daf58c262766b322c0743ba87</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDproblemStructure</name>
    <filename>classsdscip_1_1SDproblemStructure.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; SCIP_VAR * &gt;</type>
      <name>VarVec</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a32149e369677780e0d86e7a05afe582c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, unsigned int &gt;</type>
      <name>IntIntMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aeb7b6bb621cdbc574ffa5b4d2bd8637b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SCIP_CONS *, SCIP_VAR * &gt;</type>
      <name>ConsVarPair</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>af2fdb0c00e91886aa3785c6add919bbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SD_VAR_TYPE, SCIP_VAR * &gt;</type>
      <name>TypeVarPair</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0284ffa2c14e3321345b50d496474186</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, SCIP_VAR * &gt;</type>
      <name>IntVarMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae67535bdc06ca47eff5ff26315ed4c51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; ConsVarPair &gt;</type>
      <name>ConsVarVec</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>abb551dd55b714c4ab531d6b69b429343</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SD_CONS_TYPE, ConsVarVec &gt;</type>
      <name>TypeConsPair</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a4cbc315bf87e7ddbeaa6ca0c021dd3ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; int, TypeConsPair &gt;</type>
      <name>LevelConsMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a8d8a4480ccdbd293b9a9094655f322ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, ConsVarVec &gt;</type>
      <name>ExplicitDifferentialMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3213d2b6dc5e5b78ce7871e8f6944975</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, std::vector&lt; SCIP_CONS * &gt; &gt;</type>
      <name>AlgebraicMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3dc2e2d9bd66c551a0ae73ef2cccf374</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, LevelConsMap &gt;</type>
      <name>AlgebraicConsMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>acd580ed11cf545006adb420133f2f650</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, std::map&lt; unsigned int, TypeVarPair &gt; &gt;</type>
      <name>VarTimeTypeMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a00f7693ac1d10182b7df169f04f91565</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, VarVec &gt;</type>
      <name>VarVecMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a920646c6f448a32b643380d633a54f5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, std::vector&lt; SCIP_CONS * &gt; &gt;</type>
      <name>PropCutMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a10d6ab7cbd880527560f5090f05d9793</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SD_CONS_TYPE</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af1fff2e53069c8a716a47cf95317b390</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>DEFAULT_ALGEBRAIC_CONS</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af1fff2e53069c8a716a47cf95317b390a695fded567692e375869cc899e3b9843</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>MIN</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af1fff2e53069c8a716a47cf95317b390a2786318d7beb848e1ba277391b860f66</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>MAX</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af1fff2e53069c8a716a47cf95317b390af5d9d071616b8fcf1901aee309e0f08f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>SOS2_LOOKUP</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af1fff2e53069c8a716a47cf95317b390a16c008a4b937bf8428146eb869a93b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SD_VAR_TYPE</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad22496ca9655817d127636f7e028f4f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>STATE</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad22496ca9655817d127636f7e028f4f9a2705d1c498a949a09e8e65d34a541823</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>ALGEBRAIC</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad22496ca9655817d127636f7e028f4f9a54ceb507b5ebbe14b23117b1e5017959</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CONTROL</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad22496ca9655817d127636f7e028f4f9a9ae082f278e169ffd8054a0ad23e7730</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; int, SCIP_BOUNDTYPE &gt;</type>
      <name>BoundKey</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aadbe82b100c18136acc795b1b7931497</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; BoundKey, SCIP_Real &gt;</type>
      <name>BoundMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a560fbc85ce5bcd9d5152f2ccc78ba730</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDproblemStructure</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>acc02780341667acc2786b8853da6307d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDproblemStructure</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0b0630219015d9b049936f5c300873b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>clear</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a33d83a60cc320c8858f3c9e9f034d711</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>doneReading</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>accddbb383a6703fa6d2622ae5da3eec4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a717d4edfb70c1e54e5e1eac480628765</anchor>
      <arglist>(SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addVariable</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>add53278c50e621d1107d57abeafb8398</anchor>
      <arglist>(int index, SCIP_VAR *var, unsigned int time, SDproblemStructureInterface::SD_VAR_TYPE type, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab9cbf8dedc710bd9eb303fd753087817</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, SDproblemStructureInterface::SD_CONS_TYPE type, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addExplicitDifferential</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a9af51add38dd2a2006cf7aa3de78e9fd</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a8b72e8186577b242201ca895f84fe85a</anchor>
      <arglist>(SCIP_CONS *cut, unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>registerTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a645b4c81630dba4fa35adfd7cd6e0224</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>abd36733869e713366fc0ef843dc375e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a151875864728222fe3718d27ed250763</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>timesLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae0bf5ae58938e50c926302730e3eb00e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>incrementTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a12e71a78608d8b5e845d7bc7a3a7a5a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getCurrentTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a4f534e66592d4e9c4e5a3281a64f2fe1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getLastTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab525b49ccdf10d33cf1858c2f02e46cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0574eb2f7df7fc3f8a0c9fda4388026b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>varsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aa1b75682dea930832c9427322eed259a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a7a28765b108acba9b4b269a200149f09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SDVarBasic</type>
      <name>getCurrentVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a866bc732b735928523d66347668b2516</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startStateVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a142c26cd0d51cdc0243a885c5c2568f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stateVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a063cf589d845e8ddc0e5ce3a3aac9b7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a581f94749cad456cea03a5ad66b1acfe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aafd9a077739f553dbb51b08aaf2ab14c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a45359d6d24295457004fc9c9e20c0a7b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aaafe6a48103cf564fc009aa172f887c1</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>af9750fde1be733ecb749718157468182</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a8133faf0f9e5d5d5057dc432afab4de7</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementDiffCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ac19cc94432794f998fce648097f8f11a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getDiffConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3ca27baf7ae477d0eeb1d3f292961c5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_VAR * &gt;</type>
      <name>getDiffConsLastVars</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a1f115e8b6d8d4ea87f99be3d145682f7</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getDiffConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae998ba8cb3b0cbe87e297f492c18479e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae52acb193a30d627c9ffb1f3d7b1f273</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>afec732186954b269a2bfc33c0a5af077</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a226196ae0eb803a6b66f29364b9acacb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aca06ea414a9ebb40483225a0470d8098</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a61b3d7ff62b7bdb0f29a982e999e168a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3c4f2621f81b1b416c20cf63ae42d195</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a2448871eea05d7090390f3ba45c9f8d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a482ef3f7fdbbdb2b3e0052638e40113b</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3a55800fbcff016c9a2b9818c4d5f145</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>abbf41dcc8fb152b199391a7edd400e9e</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a785ad14a9602742d8aeccb2ec1844a3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a87a5a1f3bf1c88683ae5a51640bcf43b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getNthsControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a09739a3080c06eeb5272a5641c797edd</anchor>
      <arglist>(unsigned int n)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>isControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aeb83163e83b358ec6fe1c5bd067c280a</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getControlVarTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aba85b809e6f4cedc302b224e4ae7674e</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>isStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a30a1e69c22581b4bbd8ca76d97560e61</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getStateVarTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0b05222d14ab5fdc45e041bc7b0e29f6</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getNStates</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ad6b36f6e23182623df0d706e925a72a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getNControls</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0e1bd5320ed8dd97ed2ea222be3299ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getStateVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab0cf03c50d85cea4c3f93a38d097e4e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getControlVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a53a7eb4e7565fd1f83d83d23119fe935</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a61a7a3d4c25c728813ed6d5895ea454c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a72ef52e17ab812024f6b597f8a1ca18d</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a01614e61a6bfc3cf60ad3f91b443f2ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ad55cd6679d95f91ee59d8e37c8617a0f</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>af1baa5676c673e53d4ad4bf450f94580</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ac7fa43da31b12f7c0a48e46b8075acad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a60e84d0f4aeb4f80935342f73e40bade</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>afd5d6e4934ca6e48ef299bcb37e06599</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a84a857c1a71a6dea44771befce2ddc5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a9433def5736814b86dd03935946002ef</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab5393bcbfb76147003d8d361f0ce98d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a73e37879cad76143b4b09cb9547ddfb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a060ac0bedd0b83df133d8187270261f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a588e71e90def7aa3b6df23c3a3d43daa</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ad5fab5f031c9617115cc46a08a4bbac1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a34c6b1e200694e989991eb4195f0c930</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab267be911425e636f1ef7fce0fd0e6d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCurrentLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae27add24a65f9173792518c501ace56d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SD_CONS_TYPE</type>
      <name>getCurrentLevelType</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3705d2ae73b3c8347bd5277107be3246</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a0938b29821bae606a2922e82b1acf31e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>af43a2bb47773827876ff0cf822b04820</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementLevelCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a2dacf8c42c8a1b4607418520a3d9bf48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getCurrentLevelConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a974d49fd0940a2dc11d9ab75875dd9fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentLevelConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>abb1321c3c14d3971c23057fa7e5b9d5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>currentLevelConsHasVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3a6bb51c8cd7c222dc7ab86d7166f569</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::pair&lt; unsigned int, unsigned int &gt;</type>
      <name>getVarTimes</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>aa6a7b8e8e4e3229ef3f3641fb443c4a0</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getNext</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a393a5ba1a2699c906d8dd84e7ee3611f</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getPrevious</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a5195d116b6bf08a8f5adfb3452b71663</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getConsTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a6c23f2f24e8270342d06e9618c51dea3</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a2fd2fd56ebeeb9a459f816d0b9414814</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setIsValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a63d901ea4c6219d16443a5914543ae7b</anchor>
      <arglist>(bool isValid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a91abe7c1fd1a065ba9d29ad88c37dc2c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setIsReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ae15b2db34dea359a2033ce32100b46fe</anchor>
      <arglist>(bool isReformulated)</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getConsRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a3e5077697de406a7eec6724265c0417e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getVarRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>a266c401b69446d686aa733008ce47ddd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getStateVarList</name>
      <anchorfile>classsdscip_1_1SDproblemStructure.shtml</anchorfile>
      <anchor>ab6a89ad970c6f78a6f5b6423655f7c1f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDproblemStructureInterface</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a5eedef14a0dc8cfd3f0c6351f95444a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDproblemStructureInterface</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>abc6a9a247c46a663a1921cb245780bb7</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRegexes</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab86b1b1a454813c0d64d32a3b0f86921</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getConsRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab41c04791e78dd0a9b8bdac80d264ce2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getVarRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a78078126f84d2a1f8f7a52500d4fc40b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isXdotContinuous</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad5144d9bc9c671f18977ba6c485a7f7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isSimulation</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a12511c72d5e988df29fadbcfb246d50b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getNAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a78a58b2c1875ad0b54ee8bb85785fd2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; std::string &gt;</type>
      <name>getAlgebraicVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a72bc14de2319150ed07be048f709afad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getVarName</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a5a060448699f45a9bef8936cab955aeb</anchor>
      <arglist>(unsigned int varId)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setStateVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a21b1cdf114a61e9f4f8dfac1265605f2</anchor>
      <arglist>(std::vector&lt; std::string &gt;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setControlVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab55aa9609c37f54f54c5cc54177cd671</anchor>
      <arglist>(std::vector&lt; std::string &gt;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setAlgebraicVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a863bd2119917fe67a3985ed3cbd4d0b4</anchor>
      <arglist>(std::vector&lt; std::string &gt;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getVarId</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>afd9ec2c688394d10b628caddd74f1526</anchor>
      <arglist>(int varIndex)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getCurrentStateVarOrig</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a8566baf783688965af3f9c27f687e51d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCurrentStateVarId</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a23010899fd26bc56e01205187dbb7aa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getControlVarAtTOrig</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a8081642ae7abd088ebf8098d86f939f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getControlVarBeginTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a60fe9fce54e9ccef38bce8699fc4d2c1</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getAlgebraicVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a44de7934b0c80d03f7f38015f07ced55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getAlgebraicVarOrig</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ae980a6b5e9265858ef10dd79b03eddf7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getCurrentLevelConsOrigVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a3f94598524d3e4a01ad9acc32eb700c5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>isTranformed</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a36c8cce0102c67187c0cf33febd3ff7e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_RETCODE</type>
      <name>setIsTransformed</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a284b1636d699719624891b5b2f7b2051</anchor>
      <arglist>(bool isReformulated)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getVarBasename</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a74393bd983d21cbe38ede886a4cea026</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getControlVarList</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a18fb9eccf06b888dd7aa01d0fdae7aa4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getAlgebraicVarList</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>abe98423d1d0de3af171aa1b2435843d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>implode</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ae87cf27c8b6f47d5d5de5ed4ebd07e9a</anchor>
      <arglist>(const std::string &amp;glue, const std::vector&lt; std::string &gt; &amp;pieces)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_EXPR **</type>
      <name>getXdot</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1c4b7b67d1aa439b9518315b418cbc03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_EXPR **</type>
      <name>getXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af4dc6453f43027dc3a71bc2f30d1cf1a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_EXPR **</type>
      <name>getAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a0386c5f7b1f3dd6dbb9904a8192f1564</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real *</type>
      <name>getXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>acfffe376b9db08797ca804808739cb2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getNParamsPerTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aca21a272c44d4caf773b6e458883a6a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real *</type>
      <name>getXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1ec0c8ccb413724be33026ab7272cf8d</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real *</type>
      <name>getXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a5933671f18a3057918135b36db09bfbd</anchor>
      <arglist>(SCIP_Real time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real</type>
      <name>getTinit</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a6cad6196ed235b4b16eea6fe4542af53</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real</type>
      <name>getTfinal</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a90675af74319c8acd34239b98db3726b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual BoundMap</type>
      <name>getStrictBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a4e11a58258c184ccfb4d2857e19e75d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setStrictBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a80814560396cc004aa5c3912cd4a2eff</anchor>
      <arglist>(BoundMap)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Real</type>
      <name>getTstep</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ac6fb61a27b35f46ebe398cf01c87c26f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setTstep</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>abb1cec4c6e7ee474fde156b6a0423878</anchor>
      <arglist>(SCIP_Real)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setTinit</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab45ae570531b659500794930cfb17264</anchor>
      <arglist>(SCIP_Real tinit)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setTfinal</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ae519d20bc0635e91019dab606d0de1e0</anchor>
      <arglist>(SCIP_Real tfinal)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a14c155fcabc2d468ef67ef4c821abd95</anchor>
      <arglist>(std::vector&lt; SCIP_Real &gt;, unsigned int nParamsPerTime)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setXdot</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a30ac1f8f727ca886173bacd1a0be219c</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a18fc23e4ba217645442395cdfea411da</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad5ba1d7d595508424ec261ad9062acaa</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; algebraicExpr)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getStateBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ac2078a1f983c40baac454023a73a4ae2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BoundMap</type>
      <name>getStateBoundsMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a7550cba7de10c552554dfbffdeaa145d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getControlBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1552ef405dfe8df40195c95b68b6a380</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getMaxControlBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a9a15b1c5b5353a0dd7bbbe9ad6b023a4</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;oldControlBounds)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Interval &gt;</type>
      <name>getMaxStateBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>adcc78262b52a41d9ae25e885bbb1dd0d</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;oldStateBounds)</arglist>
    </member>
    <member kind="function">
      <type>BoundMap</type>
      <name>getMaxStateBoundsBoundMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a3ef8de16c1ac59a048d62c9c7402df46</anchor>
      <arglist>(const std::vector&lt; SCIP_Interval &gt; &amp;oldStateBounds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static sdo::ButcherTableau</type>
      <name>getButcherTableau</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a2d41a4be60e18f4993bfcfb3e6cd22d2</anchor>
      <arglist>(SCIP *scip, const char *discretization)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static sdo::ButcherTableau</type>
      <name>getButcherTableau</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a9f0afd18c1501173f60cfcd8e2d34190</anchor>
      <arglist>(SCIP *scip, std::string discretization)</arglist>
    </member>
    <member kind="variable">
      <type>boost::regex</type>
      <name>varRegex_</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a79c809dd1412828e592e4f40d25e752e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::regex</type>
      <name>consRegex_</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>abe9310aa479b03ad6905b15855828064</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCIP *</type>
      <name>scip_</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad87e5d567fefc4b0398fdac51df5d3ea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDproblemStructureExtendedInterface</name>
    <filename>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDproblemStructureExtendedInterface</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a30025823728f1a3ff3e1feff89a1f1ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRegexes</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a4d2cbb881f2c33df1c75618678a67e08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getConsRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ae6bbc12e4245799195dbd2b82a528fd7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::regex</type>
      <name>getVarRegex</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a2c0a3f488004de3f08d336b36ba6a540</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>clear</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ad25c83ab47081926488fdeab330c307e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>doneReading</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>acb76e24317d43823f6d9ceb396311b93</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a2316acc48efb89acd1c0cb11610b7290</anchor>
      <arglist>(SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addVariable</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a242738c89caac238ff45e4fa5a79ba5a</anchor>
      <arglist>(int index, SCIP_VAR *var, unsigned int time, int type)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a8ed7b893fdf274e24e529e0d721ec391</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, int type)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addExplicitDifferential</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a629d7d801490d0e01b422a08055ba316</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a4230ba7da326d6f03b94ecf65f37ae1b</anchor>
      <arglist>(SCIP_CONS *cut, unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>registerTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ab644d82ea0091f834ff2002ec65723b1</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a09ce988492b7c713eda51da4ad4d9dd4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>timesLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>af1d56e86f44e67416aaee6ac361c1bca</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>incrementTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a04ad84cb25381dc23a98c59924f9c0b9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>getLastTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ae1169e1bac49de1d342002e078e89d66</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a07bc86f2dab8908e95dc8da3510f76f8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>varsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aabe17eb021edf680933957a101d7cf93</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac05fb3e6d44010168c8c87a49caecf1f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SDVarBasic</type>
      <name>getCurrentVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ae91d0bdebde0c5074b9e476aa0cbc404</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a2e858a97bb9948ed4e88c8dbbca981e7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>adfd68deddd229b5cb355e68574904c71</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac03d80466ad242034aeb4907526e854c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>adb6362d7ea2995eabe89d78c70b1761f</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementDiffCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac8da65c659353420d1c98bd06076232e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_VAR *</type>
      <name>getDiffConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a03ead37eaf4a4b2c867d524395e5436b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>std::vector&lt; SCIP_VAR * &gt;</type>
      <name>getDiffConsLastVars</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a7e8831da2d97b0d865b7013409ab0366</anchor>
      <arglist>(int n)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getDiffConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a8cbc9c6051849721c672bb1b47b48f95</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aa5d13561a1168250bf837b68e0f0360f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ace0359da7fe8ab3d86a5d08812e9e101</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a7dc7e273cd34db7df9d821f6c5c66ee7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aeb5f713224c068eb87992c1ffa4bd8bf</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a7520d991b7b2498f9e38d8c8bb2c7f84</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_VAR *</type>
      <name>getControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a93c81075d951dab6e8463fae98fa4682</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a046b2ff7a785c93c26b3882819f60032</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>abc59ffccb3faf9cb1a2bce019a52009e</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac1145f09fe2801f8618c1268b13d506a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a3734b55fda9f587bdaeba85285312718</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a42576bfc8cfc2932310942572fb1c4bd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>abc2f3e32e9f0f4b20cfe841ac869b187</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a2895425187744dbdebc8d014af5da7bd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a4b3f5a719b65d596cdef06b7378baf0a</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ad7078015ee130e0fd1e6ffad27ee42ca</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a6e6374eaf9e5dce1127106fc894645a7</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a502c465dbb0eef98cd39d711e40e7859</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a5d8e71a483c172024977bf9558353182</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a16963837214cc836bc269f54750acbff</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>af9d14dd1f76568b9f1b4140f0c6910fb</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aef208e4a5df61ecdd68dd5a4cfc63827</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac7934a5433dd8db47c7926501a28aaad</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a37b18ff850b08562e11bc83487ffb005</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getCurrentLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a5f63d563c3ffb5959a39cc80d584dd60</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getCurrentLevelType</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aea1fcb71dfe934dd5ca195c6fcd28582</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a571d33053bd78b534a9a7fd0ad05d5ab</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a76094d610186ab136c49049ac3a0c098</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementLevelCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a4517bfeb8210dcb2522cca2d261271cf</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getCurrentLevelConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a692ac32c4263eee2f075968d501258d4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_VAR *</type>
      <name>getCurrentLevelConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ab2e5d2942a6a3eb4df4b52a6b5175c58</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>currentLevelConsHasVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ae41a085e07d921a26fab757993185c4e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::pair&lt; unsigned int, unsigned int &gt;</type>
      <name>getVarTimes</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a0cd54f3b01e515aaac4a386bb233b654</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getNext</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aecea87b3119a35655334bfffe0986eeb</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getPrevious</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a3bfeade50a813bd3a3d0762b3af7e88b</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getConsTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a0205ee46b8e9a5552d8a79daa22956c4</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>aea89a77cc42407ead45fca7296ddc5a8</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>setIsValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a17f8b4b6c1b6bd656ef642ebd70039b7</anchor>
      <arglist>(bool isValid)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>ac53894037a4c979ff86ab7c6f3d39be6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>setIsReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a45eb4a28ea40ab18da77168b227cc7f2</anchor>
      <arglist>(bool isReformulated)=0</arglist>
    </member>
    <member kind="variable">
      <type>boost::regex</type>
      <name>varRegex_</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a5edcd0118e2c5d898d480d5aa2a1b431</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::regex</type>
      <name>consRegex_</name>
      <anchorfile>classsdscip_1_1SDproblemStructureExtendedInterface.shtml</anchorfile>
      <anchor>a95d5ad62de4a53597212b63117a0a2e7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDproblemStructureFactory</name>
    <filename>classsdscip_1_1SDproblemStructureFactory.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SDproblemStructureFactory</name>
      <anchorfile>classsdscip_1_1SDproblemStructureFactory.shtml</anchorfile>
      <anchor>a084c287021c579d609de425c528d4a16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDproblemStructureFactory</name>
      <anchorfile>classsdscip_1_1SDproblemStructureFactory.shtml</anchorfile>
      <anchor>a9659a44de9f5899915ef6a8d62e9254b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SDproblemStructureInterface *</type>
      <name>create</name>
      <anchorfile>classsdscip_1_1SDproblemStructureFactory.shtml</anchorfile>
      <anchor>a2be0f2cd411e9e7869999ece012a34ab</anchor>
      <arglist>(int version, SCIP *scip)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDproblemStructureInterface</name>
    <filename>classsdscip_1_1SDproblemStructureInterface.shtml</filename>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>clear</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad571b38447ecd127794a46290002a0aa</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>doneReading</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ac35d3426e222c206a9365c67878785ce</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aa696b74d4db029be8d3873e90b729a16</anchor>
      <arglist>(SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime, int sdVarId)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addVariable</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a57ac8c3ab77e1010e1de02db193d089f</anchor>
      <arglist>(int index, SCIP_VAR *var, unsigned int time, SD_VAR_TYPE type, int sdVarId)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a61dde2f538a5aa759feb6fd1c71c5dbe</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addExplicitDifferential</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af777866d21e634e889f0227b2df2b430</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time, int sdVarId)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>addCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aca2cc5de7cf248328755e839f5f314d6</anchor>
      <arglist>(SCIP_CONS *cut, unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getNStates</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a18d1916642507e0d698a8c335f25f23f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getNControls</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a8c4c13b64c5006fca3ccf7edb7effa99</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; std::string &gt;</type>
      <name>getStateVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1f4c30fe3e64d1b214429c97a03e4e00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; std::string &gt;</type>
      <name>getControlVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a22c109bebde6ad4c7e0816d0af89308e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a996f4602612fa02b8daf88fd4af442b8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>adb5140d3a2023bc343a2bbba22229d2a</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>timesLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ae71872847fb34210bacfaff6b8082d05</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>incrementTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a403b9b42a1ffb5359c5a3df2668a517f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getCurrentTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a2b5133fed57052b9da3cd8a6a37ebb33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>getLastTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a5d37ceb9306e8770486dd26dadd652cc</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a2e05a16e8f7fd19c489a16a6290c5eec</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>varsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a8ce33ab4deba7cd46b6b9f29b9981340</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a4f4d3813201a6c8e72cc7b5ac91ef13c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SDVarBasic</type>
      <name>getCurrentVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a6432f0a5d60c1d299878f98ca30e6272</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>startStateVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a9b32c01dccd87872a77449f553d7fdbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>stateVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1df7561c8a2cd0bd4f761feb24053f31</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>incrementStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a0c2de81cfa25679ccfb607ca82ce0e2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getCurrentStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad052193e27fc7782b7b94a2de2b99969</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a247906ab0b41dfdfe3de8e3f2cfb0028</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ac999db2d451c915954043924f89057f4</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a29886269728943a0343506b895acee8f</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a7f41f51d15a147440df9d09516fccc7b</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementDiffCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a373d4858909368bcd4c8dff9b91d1e3e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_VAR *</type>
      <name>getDiffConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a19a610176bd9a3677520708324defc3b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; SCIP_VAR * &gt;</type>
      <name>getDiffConsLastVars</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ad61960b4f66dcd87cdcc6de26022c761</anchor>
      <arglist>(int n)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getDiffConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af7949ff973bc543c7e14caf5128a5ae0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a79acb3c394724eeddfce2589f0fb115a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a69db992f1764f5e2a2a75c9aa785518f</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af2ac0eb2e23f5dd08d9692ba0e84abd7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a663c46085aa65e1dd450ab3f41e15e5c</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a6f18836ed7e61699b063d7e2fa03ee0c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_VAR *</type>
      <name>getControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a82cdda092e0aab47fce9ec397d43c90a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>acd0174e55d4a0ad87ff39142c6a16bde</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a9f06634b1ae851f909bdea10a77b80cf</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aaebd37fa06bf4327771198852294336f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a12692e96cb216abdbfd0be809fad6874</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>incrementControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1027ba0dee6ce60782b536ce78b5ebef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a7141a1cc90609216271bc0bcf1f0e58b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getNthsControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aa9251ad72e792748ba2bc5335cf9f894</anchor>
      <arglist>(unsigned int n)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Bool</type>
      <name>isControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a3ef22de500ff2724afcfd6538ab103a4</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_Bool</type>
      <name>isStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a4c6ea17070dd92573e9f3321db6285bb</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getStateVarTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a75bb474bb734d3c67445b4a9cab42f82</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a388025533ab16de374105b7885b44095</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>startAlgebraicConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a7d6dcf2cf027d64b72837c260f171b44</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a2f4d05756fcd93922a38343f77412d6a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>algebraicConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aac882d0e113c049ad6586e8d0cd9c681</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>incrementAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a0f59ad4ac8a56f61fb1e9ef243066a25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_CONS *</type>
      <name>getAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a5d7468c7a0147904a170c4378ef4f748</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aee45d7f5edbd7fc78df7d07569eedf1e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a648960d07184d6fd1beea929fb0845c9</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a76c845ecf411a5a74ca4850057a305cd</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a2e71931987fa305f60b2f0d74c7e64bc</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab355d8bf55b503a25f65a0c5c2ded01c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a1c718f387b04e7b27f746468043fa4b4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ae921435410b4c7b8118865a5d0c3337e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a182224e3ab21f446984983c729460e08</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a45b10e72c6327b513f71d53f5450a62e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a294a6442bcd86e09936e3273e84163ae</anchor>
      <arglist>(unsigned int time)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a4321f94f0fb42af4e107159c86a926d7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>getCurrentLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ab34240a38d2a6e64d3475dbbcd67953c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SD_CONS_TYPE</type>
      <name>getCurrentLevelType</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a63f97b98bd74a6ff41f5a9ac9a977012</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startLevelConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a75553eba5d8364bafc18890d02471d24</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>levelConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>ac0229f5eec76f9ac26bcee8fde44b6b5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>incrementLevelCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a7e456e773efc0b711df9cd5fe688a1e1</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_CONS *</type>
      <name>getCurrentLevelConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a6422cb61ef34f1e849d89d6b3e6b71ac</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getCurrentLevelConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a88218c13e92ca6f654ef68caa6dc4d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>currentLevelConsHasVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a90c634cbae4c643f015fb3798a25f80b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::pair&lt; unsigned int, unsigned int &gt;</type>
      <name>getVarTimes</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a6dd506e522547fa522a719e724882c1e</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getNext</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aaa1a5e9b13c998ae69973a5342f95b34</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual SCIP_VAR *</type>
      <name>getPrevious</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>aece1613e72d825892d149bed8a3ced23</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>getConsTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a38117e4f1c100820e3b8f8a89d32a3f5</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af9705cfc20999e59d486d5ffa66d000f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>setIsValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>af9e07d5426aa834fa9d065743bf7af3f</anchor>
      <arglist>(bool isValid)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a8adef38ea0cb82a2089b92311ea62d8b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual SCIP_RETCODE</type>
      <name>setIsReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>a4497503421400ef41b04681b3a8a5bf8</anchor>
      <arglist>(bool isReformulated)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getStateVarList</name>
      <anchorfile>classsdscip_1_1SDproblemStructureInterface.shtml</anchorfile>
      <anchor>adffd4bfbee0b1da9b4f5f3aceb388cc3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDproblemStructureV1</name>
    <filename>classsdscip_1_1SDproblemStructureV1.shtml</filename>
    <member kind="typedef">
      <type>std::map&lt; unsigned int, std::vector&lt; SCIP_CONS * &gt; &gt;</type>
      <name>AlgebraicMap</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a9ae3bb9a3444d13bbf169815a0758cf6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDproblemStructureV1</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a890a8f7107cc0a5f139b919573482e5a</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDproblemStructureV1</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>af03bba36ed51e5f5282f2b526153de97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>clear</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa7e334e88a64770e292e314f388b888b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>checkIsSimulation</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a705dce1194c65b6ecad1c4f76a95b56b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSimulation</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ada2359a194b051d39c7d103085803986</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>isExprContinuous</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a3260066aa47ddc89142d278257f70752</anchor>
      <arglist>(SCIP_EXPR *expr, SCIP_Bool &amp;isContinuous)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>checkXdotContinuity</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a031ccbd79e5025d8b28fc680abcc1ceb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isXdotContinuous</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a912992e8de587d005a8c525ed68760f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>doneReading</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a563c93dcd0fcbcd4d6b673ebacde4a79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a5f36d94bfdac17cf4eed73eca649ae55</anchor>
      <arglist>(SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addVariable</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a2887203278f8cec679eb19f94d10fd09</anchor>
      <arglist>(int index, SCIP_VAR *var, unsigned int time, SD_VAR_TYPE type, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addAlgebraicCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a21334d8a2a9216171b02e7c075fddcb3</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addExplicitDifferential</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac106a176ca617dea36cf5287d3e83c60</anchor>
      <arglist>(SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time, int sdVarId)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>addCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>adb8de5e4ce4b4da59800931bfb792cbf</anchor>
      <arglist>(SCIP_CONS *cut, unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a99f1138f6b7545de2e12669c4de7d8cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>startTimeIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a19d514af50efbb009becb63b972ca2e8</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>timesLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a8bbc9dfa1a50029eb1edf7eeac85c8b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>incrementTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab1d63f78725aecb8cbdd7133648b7b97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getCurrentTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aacb842b211c9c5bbdd736979f3be0915</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>isStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab9f3802be2949c2915e50864bcf6a3b1</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getStateVarTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa94fb08f9a3493d0eb42a7441c1cc675</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Bool</type>
      <name>isControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aecb4256e75f4a18a6e8fba7f09995ac0</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getControlVarBeginTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>abfda5081152f0253bfc950252a5a20b5</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getLastTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab6c061052df0d6b258a44f1088928150</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a3e0fc95bb88a809e6eb4607a262819b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>varsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>adb5ccf7d23f8c7c6365b2dd3e6a61379</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a901397455b0010e49d1ab509d00d4a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SDVarBasic</type>
      <name>getCurrentVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a9b2d8cee953b1274f819de8ec5afe729</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a69a36e6594961863391051418fa8ccf0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startDiffConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae465d783d94c77b587a9cfabcb442770</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a9aec97132e9b56fb400725d2169861fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>diffConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a9428c821118d4d165ea0226746972461</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementDiffCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a75dfb9b829bdb3406aea9de66097e30c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getDiffConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a0bbced3e63883ab4ef00e407a92ac0d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_VAR * &gt;</type>
      <name>getDiffConsLastVars</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a47335b567b6ad5b46059968c2311e96f</anchor>
      <arglist>(int n)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getDiffConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a6b0f68a9ef64bd037efd1a80cb558070</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a6516151349f6cbb2e13e4592d5a570c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a30832d2b15bbef9576f8b6d0e0afd12d</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>af89083d229fd503b23936d48a21cccb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a212abbdd29c57caad9893580920e1c8f</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac6e21e1d3a0026cac4c5d2aba13a1233</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a30430db153a1d48d0b6bd854cdeea764</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a8e2ce0799b2e93e51a1e1611ebdcf328</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startControlVarAtTIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab43eb9b9d15083000b250e821c5935bb</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae727aeefcbde3d76fef59a8ea95d47e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>controlVarsAtTLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>afbb416928dc2c02d26943f94408509b9</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a9445bff8f26efb71b1d5aa4c31996226</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getControlVarAtT</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a151ffcbac99737164fa541a21cc8d76f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getControlVarAtTOrig</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>af07ace5e435be0a6e996455475b28513</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getNthsControlVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a4d441351b23bae7f807c72b7d9da3e20</anchor>
      <arglist>(unsigned int n)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getNStates</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac910daff769f888ccda5b1212908d39c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getNControls</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aca825cf02eef81c232d308c803616b67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getNAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a856b0452128996073a56db988fcf51ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startStateVarIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>abb393384a0d16e498bae8536c4685c60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stateVarsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae4b8dbb4cf8327b39725ccffdfc816e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a43f6913666c7f01fcecb4722c43b0fcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentStateVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a6c92b2550e05143e2146e0ff97f99eac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentStateVarOrig</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a8be209fcf66060266b59a03086ff9216</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCurrentStateVarId</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a0e90a569a742384ecff51068ea102343</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getStateVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>af90e265b3c7a80178e36e56f4af8a50e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getControlVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aedc070846dcf8e28bd4d1f8e543632ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getAlgebraicVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aee0fd9fefdefa12d9b9db979226c83a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStateVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a2114af24ad885e58304e650d1acfa03a</anchor>
      <arglist>(std::vector&lt; std::string &gt; stateVarNames)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setControlVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aac8e8582622d879023c9a85fc566e967</anchor>
      <arglist>(std::vector&lt; std::string &gt; controlVarNames)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlgebraicVarNames</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a52d7a4430cbf638c87d9ede02923df7b</anchor>
      <arglist>(std::vector&lt; std::string &gt; algebraicVarNames)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR **</type>
      <name>getXdot</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a8105a98353bef34b5392b3682e9bf294</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR **</type>
      <name>getXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a4f245444a4930987e4a0b772a8b38d1e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR **</type>
      <name>getAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad7741c0dd1988af0aa0cde1fb9838e03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real *</type>
      <name>getXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a35eb68315eec8383034c55515856c1f7</anchor>
      <arglist>(int time)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNParamsPerTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac2b53703e738f7e798d505740dc60549</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real *</type>
      <name>getXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa76f2e7f6136b98203ee2191b574aa87</anchor>
      <arglist>(SCIP_Real time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdotParams</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a087f82ffbb8a18ae4c31395cb0dd35eb</anchor>
      <arglist>(std::vector&lt; SCIP_Real &gt; xdotParams, unsigned int nParamsPerTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdot</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa2d54e69ba945da2a3c05a3376a8343e</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; xdot)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlgebraicExpressions</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac896cbec09b3ec7614e6c6f43ed754fb</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; algebraicExpr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad058eb8957874e74911b9d85d897525f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startCutIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a434fc12a4be4b11158c8d391c838da71</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aec9d9447d71db6c7f6a77f1a2eb73daf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cutsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae5dd438df194ba099f033c0267913619</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a4ea22d3d64ba957b68f6633802acb3b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getCut</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a18d8d745f4997db0196df3b8c6695efd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa92f31ac5a92dd2d9c213f125899f616</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a3f111c37fab602cb2de68380c11418b0</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aa306a2d41d58d7ddbed8e9ca6d1caaea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab5059ffe6e03598e3371cf27fa6dde19</anchor>
      <arglist>(unsigned int time)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a1ebf5a197506cfefbc60881f260f06d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCurrentLevel</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a48aa0546dc86757348f7f940666200f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SD_CONS_TYPE</type>
      <name>getCurrentLevelType</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad2a2a30a4d46925eea78e7a15dd0e3d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startLevelConsIteration</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab19fc964e1b152374d82253f51730ee8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>levelConsLeft</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae3928b66229608c914d49c89e8ae1cef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>incrementLevelCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad80d54fbf5cce2c28a8fbbdb77e9e698</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_CONS *</type>
      <name>getCurrentLevelConsCons</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac5cf38925cf63f0736c3a7618087df8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setXdotAlgebraic</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad8377b68de5741d2343130bcb2d53017</anchor>
      <arglist>(std::vector&lt; SCIP_EXPR * &gt; xdotAlgebraic)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentLevelConsVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a184f921617b3ed72a39d3acf8cce34c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getCurrentLevelConsOrigVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>adba62b9f876c40981ffdd9702dab05d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>currentLevelConsHasVar</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a22161e4390c80f5fc2757e8f0b701984</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; unsigned int, unsigned int &gt;</type>
      <name>getVarTimes</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>af051431a5fc58db4a72f72594c2251ae</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getNext</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad7d15bf94389386db283bec563a214ce</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getPrevious</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a47b19c67b733ff7469f3152e78b85842</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getConsTime</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ae21a13012893294e8716586fc9ac6deb</anchor>
      <arglist>(SCIP_VAR *var)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a91651c40c28a8cc9a1f0ec4ae0162acd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setIsValid</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a37d922172376bc4e0cc9f837aed77deb</anchor>
      <arglist>(bool isValid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>abbea5869c799fcc75523d80c084d38dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setIsReformulated</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a6e48d1a3fc4db3ab6e7ed0558b2911d9</anchor>
      <arglist>(bool isReformulated)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isTranformed</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a2910a268991e113c354ca5e1047e1940</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_RETCODE</type>
      <name>setIsTransformed</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a82a99fda7e7c443a9a2b80cefe887bb5</anchor>
      <arglist>(bool isReformulated)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getTinit</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a55be7f50a5eacfd4e74dd9b1c79b255e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getTfinal</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>abb81bdfaf6f098d8e5d903aa9e6e0c44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>getTstep</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ac37e1ccf1eef1ea3c006375efb4c73b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTstep</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a2a3d4943c494a8bd0f48af3018d88643</anchor>
      <arglist>(SCIP_Real)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTinit</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ad3d07cd7a3e04cdbe89c9077b270abef</anchor>
      <arglist>(SCIP_Real tinit)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTfinal</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>a2f2f059ea3a99016322725b971d2f04c</anchor>
      <arglist>(SCIP_Real tfinal)</arglist>
    </member>
    <member kind="function">
      <type>BoundMap</type>
      <name>getStrictBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>aaaba95bb18f5d024eb5eb72f11c600ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStrictBounds</name>
      <anchorfile>classsdscip_1_1SDproblemStructureV1.shtml</anchorfile>
      <anchor>ab52164c326aeaa7c05b2167897010d7e</anchor>
      <arglist>(BoundMap boundMap)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDSCIPtest</name>
    <filename>classsdscip_1_1SDSCIPtest.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SDSCIPtest</name>
      <anchorfile>classsdscip_1_1SDSCIPtest.shtml</anchorfile>
      <anchor>ab8be98ecdab3dba81a4be52784f92081</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDSCIPtest</name>
      <anchorfile>classsdscip_1_1SDSCIPtest.shtml</anchorfile>
      <anchor>a6f0a4962b2b4582d475cea56fe45cc26</anchor>
      <arglist>(SCIP *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDSCIPtest</name>
      <anchorfile>classsdscip_1_1SDSCIPtest.shtml</anchorfile>
      <anchor>a1614f2f559c451683b019e2ee760f28c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testEqual</name>
      <anchorfile>classsdscip_1_1SDSCIPtest.shtml</anchorfile>
      <anchor>aff7e8c78292fd86360d05c5d0a2c9305</anchor>
      <arglist>(double a, double b)</arglist>
    </member>
    <member kind="variable">
      <type>SCIP *</type>
      <name>scip_</name>
      <anchorfile>classsdscip_1_1SDSCIPtest.shtml</anchorfile>
      <anchor>a33d02d24e5f0323610b4c3d25bfa46d8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SDVarBasic</name>
    <filename>classsdscip_1_1SDVarBasic.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SDVarBasic</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a4f71a97fd0321051055239e61bddfd9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SDVarBasic</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a71fff450ce48724974acbfb50e4636f0</anchor>
      <arglist>(SCIP_VAR *scipVar, unsigned int time, int type)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SDVarBasic</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a8962125fc4286b1442b5ca3fb066df6d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a307df43c31472f85e05f7c0991a379c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_VAR *</type>
      <name>getScipVariable</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a509af3ab27fe9fbd6557a5e7e1d265c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getTime</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>a811cf80e45a7e31ec1a052f3fa038f89</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getType</name>
      <anchorfile>classsdscip_1_1SDVarBasic.shtml</anchorfile>
      <anchor>aa6d10ef86d042eac775a3bb3aa98f77a</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::SimRateEvaluator</name>
    <filename>classsdscip_1_1SimRateEvaluator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>SimRateEvaluator</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>a38480fb33ab608e59a336455c0dd771a</anchor>
      <arglist>(int _nStates, SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SimRateEvaluator</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>aa56ba582d22b7be2eff261986b0dd46f</anchor>
      <arglist>(int _nStates, int _nAlgebraic, int _nControls, SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SimRateEvaluator</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>a6608fba942d14ba7230f95e36ffd46b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>ace3991da20fd4818b6deb5676d53b46e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PointRateEvaluator *</type>
      <name>clone</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>a7d1286201ea96407e029dc09c405f34d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>a320fe83763a80380820f3e1945cb86bb</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>getRates</name>
      <anchorfile>classsdscip_1_1SimRateEvaluator.shtml</anchorfile>
      <anchor>a8b2f241a867823f22f3eeb774d31dd40</anchor>
      <arglist>(SCIP_Real t, std::vector&lt; SCIP_Real &gt; states, SCIP_Real *params)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>sdscip::Statistics</name>
    <filename>structsdscip_1_1Statistics.shtml</filename>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>structsdscip_1_1Statistics.shtml</anchorfile>
      <anchor>a6ecae1b16af609c445e62b85b976f9d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Statistics</name>
      <anchorfile>structsdscip_1_1Statistics.shtml</anchorfile>
      <anchor>a1649c5e995b316cf39e5bfa9fca14cbe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>SCIP_Real</type>
      <name>remainingBounds</name>
      <anchorfile>structsdscip_1_1Statistics.shtml</anchorfile>
      <anchor>a095a6ad4eb3453772b3d4628bfea6afd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nSubscips</name>
      <anchorfile>structsdscip_1_1Statistics.shtml</anchorfile>
      <anchor>aa0db8b20d817a7b068afacb50d8ce074</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestBoundMap</name>
    <filename>classsdscip_1_1TestBoundMap.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestBoundMap</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>a8d3bc77f2dd62938124ac327d3c39224</anchor>
      <arglist>(SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestBoundMap</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>a797e61f91a8048fdd08e94325e5fa3c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNsuccess</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>ac169a4f4fe6a7bf97658d65f13069b4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNerror</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>a2a0c5039775b15474deba4be83bfa90a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>a53737e1215ac9cd53109b78b2f4ae886</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testOperations</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>aef1c40d22ad7984841f3cb8d0b1cbbfe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestBoundMap.shtml</anchorfile>
      <anchor>af05a08bacec552840ac621a61dfa2f44</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestEstimatorTypes</name>
    <filename>classsdscip_1_1TestEstimatorTypes.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestEstimatorTypes</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a71f8ef8f6dbdc09d8935bbc9d67947f3</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TestEstimatorTypes</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>af9d275107d72479ab5965cbca7208ff9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a53babe4415018775a75123541a6cfd70</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addE1E3tests</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a7415cba91d1fda7e7889ebc9ed7fa408</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addE2E4tests</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a8746aef9f608502e6b247af70a6ba15e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addE5E6tests</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a607f871bb42c44a2c1cd3ad142362429</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runClass1EstimatorTypesTests</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>ac65f98992aae40f3c45c5cdea9c13ba8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; SAFE_ESTIMATOR, double &gt;::const_iterator</type>
      <name>findSmallestErrorIt</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a5ce36e0f712c5694aa8c5e2a52c30b1e</anchor>
      <arglist>(std::map&lt; SAFE_ESTIMATOR, double &gt; errsAtX)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runTests</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>a8b882753141ac2fa224a733a5b3d2b93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>ab46848f3c5893ea595673d5ed329b80f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TestExprPiecewiseLinear</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>aeb99327735c37c4bbd4f5e41d1b103e1</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestExprPiecewiseLinear</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a57349303e1044069e702b0a6927c052f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>aac9c66e8c50a0388711258b49cc9e78c</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
    <member kind="function">
      <type>SCIP_Real</type>
      <name>evaluateEstimation</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>ad85eb7c2f67c3b5ea9993cbfc4ed9ed9</anchor>
      <arglist>(EstimationData estimation, SCIP_Real x)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>estimationToString</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>adbb790e6a7599e4891320d68222a3b71</anchor>
      <arglist>(EstimationData estimation)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>compareEstimationSpline</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a96cf0bef6748ab81dc5fe8c6af0b6cfb</anchor>
      <arglist>(boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt; pcwlin, EstimationData estimation, double argval)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeCoincidingPoints</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>af07c0d2cee5c7c78b7bdaccd493c98ed</anchor>
      <arglist>(ValVec &amp;xvals, ValVec &amp;yvals)</arglist>
    </member>
    <member kind="function">
      <type>SCIP_EXPR *</type>
      <name>createExprPiecewiseLinear</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a70e1254e11beb24737983ba525801485</anchor>
      <arglist>(EstimatorTestData data)</arglist>
    </member>
    <member kind="function">
      <type>EstimationData</type>
      <name>getEstimation</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>aa6cc5a4633c5d58d7519324541d568ad</anchor>
      <arglist>(SCIP_EXPR *pcwlin, SCIP_Real argvals, Bound argbounds, bool overestimate)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sampleEstimation</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a9c96d2ca5574dead62eb084cb8b6b9c4</anchor>
      <arglist>(SCIP_EXPR *pcwlin, int nPoints, Bound argbound, EstimationData estimation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addManualEstimatorTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>acf51eaf88fe1ef72a3d2a6ce1ecc28ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addRandomEstimatorTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a9eb3d054c6fb271b80255274c54985d1</anchor>
      <arglist>(int nTests, Bound xrange, Bound yrange, bool integerDataPoints, int nArgBounds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addNumericsEstimatorTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>aa691917f4cb0ad492439ebb01c66c902</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a7e0099811484ea2a96104d1e8faf3981</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a8b4f81653f6d0cbe24e20472bf4eb0d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a050f6ec00955173f5faae0285d3e7411</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runEstimatorManualTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a50f2143c4b1a681ed90648af9e8d7cfb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runWorldLookup</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a15452390faba78faa23bc913faf8dd3b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runEstimatorRandomTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a11151a1f6222d8419580d3ff9a238421</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runEstimatorNumericsTests</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a4ce1f607d6388d73fc2c9addb239953d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>af8007a64cc49bcb623c75d8f5152612f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TestSDplugin</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>a2d9af50091ee42c8a864b78bc05e2a9d</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestSDplugin</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>aafe31943149fe4827ee2f37cf3bc583f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getRandInt</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>abb250c00ab67a47cb90edce06b5b867a</anchor>
      <arglist>(int min, int max)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getRandInt</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>a1fc7ecba7446fc44f46a72967b7b5a37</anchor>
      <arglist>(double min, double max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getRandDouble</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>a6833018ba62202e1d57866fc7f0d76c0</anchor>
      <arglist>(double min, double max)</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; EstimatorTypeTestData &gt;</type>
      <name>typeTestsData_</name>
      <anchorfile>classsdscip_1_1TestEstimatorTypes.shtml</anchorfile>
      <anchor>abc88dafe55b39fd12e1626bdfb888e98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; EstimatorTestData &gt;</type>
      <name>testsData_</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a38390205f4f06d927adbf4bf1eaac2a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>tolerance_</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>add0a88f6ab2b9db766f5de0728c6310c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>zeroTolerance_</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a09150d3557996768a2634718a29d5a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; SCIP_Real, SCIP_Real &gt;</type>
      <name>Bound</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a497c223c1cb5739b268e4fd3a1b7fa76</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; std::pair&lt; SCIP_Real, SCIP_Real &gt; &gt;</type>
      <name>BoundVec</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>ac67c40c3bd644edf3284e1fa62306765</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; SCIP_Real &gt;</type>
      <name>ValVec</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a0b3f5b79aaa4ad1b99410129f8671aae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>verifyEstimation</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>a1fe30d0a15181a556c910e107db37090</anchor>
      <arglist>(boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt; pcwlin, EstimationData estimation, double argval, SCIP_Real tolerance)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>sampleEstimationAtKnots</name>
      <anchorfile>classsdscip_1_1TestExprPiecewiseLinear.shtml</anchorfile>
      <anchor>aa34261765d9a33e38c8930e04addca07</anchor>
      <arglist>(boost::shared_ptr&lt; spline::BSplineCurve&lt; 1, SCIP_Real &gt; &gt; pcwlin, EstimationData estimation, Bound argbound, int &amp;localErrors, SCIP_Real tolerance)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SCIP *</type>
      <name>subscip_</name>
      <anchorfile>classsdscip_1_1TestSDplugin.shtml</anchorfile>
      <anchor>aed918260396e04f702e375756d1e7c80</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestExprPiecewiseLinear</name>
    <filename>classsdscip_1_1TestExprPiecewiseLinear.shtml</filename>
  </compound>
  <compound kind="class">
    <name>sdscip::TestGeom</name>
    <filename>classsdscip_1_1TestGeom.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestGeom</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a01756c00b80ebab3a6289780b8936e7d</anchor>
      <arglist>(SCIP *_scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestGeom</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>aacda2fa11c88110624ba25f493f73b44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>ac53918bfdfce1253b92760f116c3156a</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>aab3044f7b1c37b3bec4123e05e6acb09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runCurrent</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a6e36cac39277e98b8ea5f96c77a048a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testContains</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>afbf0bc4b36399f8ea0031dca6402ac5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIsOnFace</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a589c36fbd54270751f651684114e4748</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIsOnVertex</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a3e3fdc5dac6d26dbd8044d46d8322983</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testFindSeveredVertex</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a768bce58dc13279860a8493ab597f7af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testVectorOperators</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a9759e7d00134944aeeecbfe2183c7868</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIntersection</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a8cd0d71d5a58e1d842e3847f075647d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetSeparatedVolume</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>ad1fd71700d6d837faf6043713fdd24a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testHyperCubeIntersects</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a1561865c51b9308de4d4216770043a43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>HyperCube</type>
      <name>unitCube</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>a715664009e83376f790d2f7c8ea30038</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testVectorLength</name>
      <anchorfile>classsdscip_1_1TestGeom.shtml</anchorfile>
      <anchor>afb9fe086720de89082ca649aeaaae912</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestODEintegrator</name>
    <filename>classsdscip_1_1TestODEintegrator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestODEintegrator</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a19d61bf6e3b8c550746d82bd2287365a</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestODEintegrator</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>aab50e62a717add58ed819606dbf17b6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a006daa1fce6bbe2a66bd69aaa2be993d</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNsuccess</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a4cc07062d6e0217027e8a8de612a224f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNerrors</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>aac273b95afe11e0ff8a72d1833699344</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a98e4b3e4a5d23c865c7477b303cc38f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runSimTests</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a062b00b9455b1ebf90144a7de4c9e235</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runConstRateEvaluatorTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a656bb426400dd4bff17e155637fd5732</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySimTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a71473ea9aa33651ecc6e000f9cc345f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySimIntermediateStepsTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>ac2d23a864860123dda947709a717eaed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runSBtests</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a4a8d909e947d2f54212503c7b38c6468</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySBsimTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>abeff4bac8a5b802eb1e77666d2f3213d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySBcontrolTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>aa46ccd64bdafa36bda9e642dde69e879</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySBglobalBoundsTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a7638acee5a871c9858062bc71b5aa6bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runPredatorPreySBboundsTest</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>ac88dd20c4b77307809e8c6753ab1fb72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getTestDiscretizations</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>aca48764777e1806194bb499f2be3c0a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createVar</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a977e0523fa8ac17e7d822ef8064b74fd</anchor>
      <arglist>(SCIP_VAR *&amp;var, const char *name, SCIP_Real lb, SCIP_Real ub, SCIP_Real obj, SCIP_VARTYPE vartype)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; SCIP_EXPR * &gt;</type>
      <name>getXdotPredatorPrey</name>
      <anchorfile>classsdscip_1_1TestODEintegrator.shtml</anchorfile>
      <anchor>a3f10852777045a5593e16f91de12ddd5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestSBrateEvaluator</name>
    <filename>classsdscip_1_1TestSBrateEvaluator.shtml</filename>
    <member kind="function">
      <type></type>
      <name>TestSBrateEvaluator</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>aee1ee046400dd294b442b161ba2b616a</anchor>
      <arglist>(SCIP *scip)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TestSBrateEvaluator</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>ad0407774ac965a30d916c1964104e5bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>toString</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>a2ebd49819f49e996e0eeb95e9e949c52</anchor>
      <arglist>(std::ostream &amp;strm) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNsuccess</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>ae7f7453399519d4928ce370a01ba1748</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getNerrors</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>a5a5561cfc2c6ae0720565bdeceff3183</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runAll</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>ad4e62032fffea1b8d5dd807c0f75b4fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>runBoundTests</name>
      <anchorfile>classsdscip_1_1TestSBrateEvaluator.shtml</anchorfile>
      <anchor>a0ee98858f872fcb9573ae658e3e3fea9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sdscip::TestSDplugin</name>
    <filename>classsdscip_1_1TestSDplugin.shtml</filename>
  </compound>
  <compound kind="class">
    <name>sdscip::Vector</name>
    <filename>classsdscip_1_1Vector.shtml</filename>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;</type>
      <name>Components</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>ad24406c0cd77390767cb898f2e238b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; double &gt;::iterator</type>
      <name>ComponentIterator</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a422b969c62bff666e8c5ca18e496db3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>ab63836225b228ca616219133eb7d5315</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a0926d123ec1a6e996c803dc6c75da0b8</anchor>
      <arglist>(int _ndim)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>adb22b681988f80ca070f085366d86d06</anchor>
      <arglist>(std::vector&lt; double &gt;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a92388e99263964697c7cd1c3c19e79c5</anchor>
      <arglist>(double x1, double x2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a1eb13e1d16fab44be484af99b6d2270d</anchor>
      <arglist>(double x1, double x2, double x3)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Vector</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a073e3d6893b90826f017b2e249873d0c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a32a238013bfc4c72ad163a4061ba7514</anchor>
      <arglist>(Vector const &amp;lhs)</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>ab8f774ff4f99fa31810c7ab619397051</anchor>
      <arglist>(double scalar)</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a0575bf700c8e62586cc2076b536a7adb</anchor>
      <arglist>(Vector const &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>length</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a7746e5e19b40d21671afb3ca7064995d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>vec2string</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>ad503d7747a348fefb05a2f368eba59ee</anchor>
      <arglist>(std::vector&lt; double &gt; vec, std::string message)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>printVec</name>
      <anchorfile>classsdscip_1_1Vector.shtml</anchorfile>
      <anchor>a79e7ea9ec163fd8f7b4d1c8be83834e9</anchor>
      <arglist>(std::vector&lt; double &gt; vec, std::string message)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>std</name>
    <filename>namespacestd.shtml</filename>
    <class kind="struct">std::equal_to&lt; MdlScipVar &gt;</class>
    <class kind="struct">std::hash&lt; MdlScipVar &gt;</class>
  </compound>
  <compound kind="struct">
    <name>std::equal_to&lt; MdlScipVar &gt;</name>
    <filename>structstd_1_1equal__to_3_01MdlScipVar_01_4.shtml</filename>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1equal__to_3_01MdlScipVar_01_4.shtml</anchorfile>
      <anchor>ae0c16bbafbdad5eedd09938894858766</anchor>
      <arglist>(const MdlScipVar &amp;a, const MdlScipVar &amp;b) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; MdlScipVar &gt;</name>
    <filename>structstd_1_1hash_3_01MdlScipVar_01_4.shtml</filename>
    <member kind="function">
      <type>size_t</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1hash_3_01MdlScipVar_01_4.shtml</anchorfile>
      <anchor>a3f6ef9ab7d0df458ded8382c2de785eb</anchor>
      <arglist>(const MdlScipVar &amp;v) const </arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/nfs/OPTI/bzfvierh/repos/sd-scip/sdscip/src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.shtml</filename>
    <file>BaseTest.cpp</file>
    <file>BaseTest.h</file>
    <file>BoundMap.h</file>
    <file>BoundMapHelpers.cpp</file>
    <file>BranchControlFirst.cpp</file>
    <file>BranchControlFirst.h</file>
    <file>ConstRateEvaluator.cpp</file>
    <file>ConstRateEvaluator.h</file>
    <file>CopyablePointer.cpp</file>
    <file>CopyablePointer.h</file>
    <file>cppmain.cpp</file>
    <file>ExprLookup.cpp</file>
    <file>ExprLookup.h</file>
    <file>ExprPiecewiseLinear.cpp</file>
    <file>ExprPiecewiseLinear.h</file>
    <file>HeurSimODE.cpp</file>
    <file>HeurSimODE.h</file>
    <file>HyperCube.cpp</file>
    <file>HyperCube.h</file>
    <file>HyperPlane.cpp</file>
    <file>HyperPlane.h</file>
    <file>IntervalODEintegrator.cpp</file>
    <file>IntervalODEintegrator.h</file>
    <file>Line.cpp</file>
    <file>Line.h</file>
    <file>ListNode.h</file>
    <file>LookupConsHdlr.cpp</file>
    <file>LookupConsHdlr.h</file>
    <file>MdlExpressionTranslator.cpp</file>
    <file>MdlExpressionTranslator.h</file>
    <file>NLPGraph.cpp</file>
    <file>NLPGraph.h</file>
    <file>ODEintegrator.cpp</file>
    <file>ODEintegrator.h</file>
    <file>Orthant.cpp</file>
    <file>Orthant.h</file>
    <file>OrthantList.cpp</file>
    <file>OrthantList.h</file>
    <file>Point.cpp</file>
    <file>Point.h</file>
    <file>PointODEintegrator.cpp</file>
    <file>PointODEintegrator.h</file>
    <file>PointRateEvaluator.cpp</file>
    <file>PointRateEvaluator.h</file>
    <file>PresolConsGraph.cpp</file>
    <file>PresolConsGraph.h</file>
    <file>PresolCppMin.cpp</file>
    <file>PresolCppMin.h</file>
    <file>ProbDataCtrl.cpp</file>
    <file>ProbDataCtrl.h</file>
    <file>ProbDataSD.cpp</file>
    <file>ProbDataSD.h</file>
    <file>prop_obobt.cpp</file>
    <file>prop_obobt.h</file>
    <file>PropagationPattern.cpp</file>
    <file>PropagationPattern.h</file>
    <file>PropCtrlOBBT.cpp</file>
    <file>PropCtrlOBBT.h</file>
    <file>PropOBRA.cpp</file>
    <file>PropOBRA.h</file>
    <file>PropODE.cpp</file>
    <file>PropODE.h</file>
    <file>PropProbingObjTest.cpp</file>
    <file>PropProbingObjTest.h</file>
    <file>pub_message_sd.h</file>
    <file>reader_osilc.c</file>
    <file>reader_osilc.h</file>
    <file>ReaderVOP.cpp</file>
    <file>ReaderVOP.h</file>
    <file>ReduceODEintegrator.cpp</file>
    <file>ReduceODEintegrator.hpp</file>
    <file>SBrateEvaluator.cpp</file>
    <file>SBrateEvaluator.h</file>
    <file>SDCons.cpp</file>
    <file>SDCons.h</file>
    <file>SDControl.h</file>
    <file>SDList.h</file>
    <file>SDListBuilder.h</file>
    <file>SDListTraits.h</file>
    <file>SDproblemStructure.cpp</file>
    <file>SDproblemStructure.h</file>
    <file>SDproblemStructureExtendedInterface.h</file>
    <file>SDproblemStructureFactory.cpp</file>
    <file>SDproblemStructureFactory.h</file>
    <file>SDproblemStructureInterface.cpp</file>
    <file>SDproblemStructureInterface.h</file>
    <file>SDproblemStructureV1.cpp</file>
    <file>SDproblemStructureV1.h</file>
    <file>sdscip.h</file>
    <file>SDSCIPtest.cpp</file>
    <file>SDSCIPtest.h</file>
    <file>SDVarBasic.cpp</file>
    <file>SDVarBasic.h</file>
    <file>SDVariable.h</file>
    <file>SimRateEvaluator.cpp</file>
    <file>SimRateEvaluator.h</file>
    <file>Statistics.cpp</file>
    <file>Statistics.h</file>
    <file>TestBoundMap.cpp</file>
    <file>TestBoundMap.h</file>
    <file>TestEstimatorTypes.cpp</file>
    <file>TestEstimatorTypes.h</file>
    <file>TestExprPiecewiseLinear.cpp</file>
    <file>TestExprPiecewiseLinear.h</file>
    <file>TestGeom.cpp</file>
    <file>TestGeom.h</file>
    <file>TestODEintegrator.cpp</file>
    <file>TestODEintegrator.h</file>
    <file>TestPropagationPattern.cpp</file>
    <file>TestSBrateEvaluator.cpp</file>
    <file>TestSBrateEvaluator.h</file>
    <file>TestSDplugin.cpp</file>
    <file>TestSDplugin.h</file>
    <file>TestStatistics.cpp</file>
    <file>TestStatistics.h</file>
    <file>unittests.cpp</file>
    <file>Vector.cpp</file>
    <file>Vector.h</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>SD-SCIP</title>
    <filename>index</filename>
  </compound>
</tagfile>
