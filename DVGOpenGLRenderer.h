#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKTextureLoader.h>
#import <AVFoundation/AVFoundation.h>
#include <GLKit/GLKMath.h>
#import "math.h"

enum
{
	UNIFORM_SHADER_SAMPLER_RPL,
	UNIFORM_SHADER_COLORTINT_RPL,
	UNIFORM_RENDER_TRANSFORM_RPL,
   	NUM_UNIFORMS
};

enum
{
	ATTRIB_VERTEX_RPL,
	ATTRIB_TEXCOORD_RPL,
   	NUM_ATTRIBUTES
};

typedef enum {
    kDVGGLNoRotation,
    kDVGGLRotateLeft,
    kDVGGLRotateRight,
    kDVGGLFlipVertical,
    kDVGGLFlipHorizonal,
    kDVGGLRotateRightFlipVertical,
    kDVGGLRotateRightFlipHorizontal,
    kDVGGLRotate180
} DVGGLRotationMode;
static int NUM_UNIFORMS_COUNT = 100;
@class DVGStackableCompositionInstruction;
@interface DVGOpenGLRenderer : NSObject
@property CMPersistentTrackID effectTrackID;
@property DVGGLRotationMode effectTrackOrientation;
- (void)releaseOglResources;

// opengl stuff
@property GLuint rplProgram;
@property GLint* rplUniforms;
@property CGAffineTransform renderTransform;
@property CVOpenGLESTextureCacheRef videoTextureCache;
@property EAGLContext *currentContext;
@property GLuint offscreenBufferHandle;
- (CVOpenGLESTextureRef)bgraTextureForPixelBuffer:(CVPixelBufferRef)pixelBuffer;
- (void)renderIntoPixelBuffer:(CVPixelBufferRef)destinationPixelBuffer
                   prevBuffer:(CVPixelBufferRef)prevBuffer
                 sourceBuffer:(CVPixelBufferRef)trackBuffer
                 sourceOrient:(DVGGLRotationMode)trackOrientation
                       atTime:(CGFloat)time withTween:(float)tweenFactor;
+ (DVGGLRotationMode)orientationForPrefferedTransform:(CGAffineTransform)preferredTransform andSize:(CGSize)videoSize;
+ (CGSize)landscapeSizeForOrientation:(DVGGLRotationMode)orientation andSize:(CGSize)videoSize;
+ (const GLfloat *)textureCoordinatesForRotation:(DVGGLRotationMode)rotationMode;
+ (GLKTextureInfo*)createGLKTextureFromCGImage:(CGImageRef)image;
+ (CVPixelBufferRef)createPixelBufferFromCGImage:(CGImageRef)image;

@end
