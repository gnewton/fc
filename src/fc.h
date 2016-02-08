

int MinOutSize =  0,
  Edge_Thresh = 65,
  OutputListPoints = FALSE,
  Overlay = FALSE,
  CircHist = FALSE,
  TmWaterWeight = FALSE,
  TmThresh = 0,
  SmoothCircHist = FALSE,
  ExtendLines = FALSE,
  Average = FALSE,
  AverageBlockSize = 3,
  PostscriptOut = FALSE,
  OutputSingleContour = FALSE,
  CheckContourDir = FALSE,
  Hough = FALSE,
  RotateHist=0,
  MinValue=0,
  MaxValue = 255,
  EndPointNum = 500,
  XCheck = 5000,
  TraceFlag = FALSE,
  TraceColour = 200;
  Test = FALSE,
  YCheck = 5000,
  SunView = FALSE,
  Endpoints = 200,
  SelContour = FALSE,
  Debug = 0,
  Strategy = 1,
  J=1;

char *OutputListPointsFile;



float K = 0.45;

IMAGE im_struct;

byte *image;

byte *Trace;
