#import <Foundation/Foundation.h>
#import "DVGOglEffectBase.h"

#import "DVGOglEffectKeyframedAnimation.h"

@class DVGStackableCompositionInstruction;
typedef void (^DVGStackableCompositionInstructionProgressBlock)(DVGStackableCompositionInstruction*);
typedef CVPixelBufferRef (^DVGStackableCompositionInstructionFrameBufferFabricator)(CMPersistentTrackID trackId);

@interface DVGStackableCompositionInstruction : NSObject <AVVideoCompositionInstruction>
// AVVideoCompositionInstruction traits
@property (nonatomic) CMPersistentTrackID passthroughTrackID;
@property (nonatomic) CMTimeRange timeRange;
@property (nonatomic) BOOL enablePostProcessing;
@property (nonatomic) BOOL containsTweening;
@property (nonatomic) NSArray<NSValue *> *requiredSourceTrackIDs;
@property (nonatomic, strong) NSArray<DVGOglEffectBase *> *renderersStack;
@property (nonatomic) NSMutableDictionary* pools;
@property (nonatomic) CVPixelBufferRef lastOkRenderedPixels;
@property (nonatomic) DVGStackableCompositionInstructionProgressBlock onBeforeRenderingFrame;
@property (nonatomic) DVGStackableCompositionInstructionFrameBufferFabricator onTrackFrameNeeded;
@property (nonatomic) CGFloat actualRenderTime;
@property (nonatomic) CGFloat actualRenderProgress;
@property (nonatomic) CGSize actualRenderSize;
@property (nonatomic) NSValue* actualRenderTransform;
- (id)initProcessingZero;
- (id)initProcessingWithSourceTrackIDs:(NSArray*)sourceTrackIDs forTimeRange:(CMTimeRange)timeRange;
- (id)getPixelBufferPoolForWidth:(int)w andHeight:(int)h;
@end
