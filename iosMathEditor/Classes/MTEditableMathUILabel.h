//
//  EditableMathUILabel.h
//
//  Created by Kostub Deshmukh on 9/2/13.
//  Copyright (C) 2013 MathChat
//   
//  This software may be modified and distributed under the terms of the
//  MIT license. See the LICENSE file for details.
//

#import <UIKit/UIKit.h>
#import "MTMathList.h"

@class MTEditableMathUILabel;
@class MTMathListIndex;

@protocol MTEditableMathUILabelDelegate <NSObject>

// Called when the return key is pressed
- (void) returnPressed:(MTEditableMathUILabel*) label;
// called when any text is modified
- (void) textModified:(MTEditableMathUILabel*) label;

- (void) didBeginEditing:(MTEditableMathUILabel*) label;
- (void) didEndEditing:(MTEditableMathUILabel*) label;

@end

/** This protocol provides information on the context of the current insertion point. 
 The keyboard may choose to enable/disable/highlight certain parts of the UI depending on the context.
 e.g. you cannot enter the = sign when you are in a fraction so the keyboard could disable that.
 */
@protocol MTMathKeyboardTraits <NSObject>

@property (nonatomic) BOOL equalsAllowed;
@property (nonatomic) BOOL fractionsAllowed;
@property (nonatomic) BOOL variablesAllowed;
@property (nonatomic) BOOL numbersAllowed;
@property (nonatomic) BOOL operatorsAllowed;
@property (nonatomic) BOOL exponentHighlighted;
@property (nonatomic) BOOL squareRootHighlighted;
@property (nonatomic) BOOL radicalHighlighted;

@end

/** Any keyboard that provides input to the `MTEditableMathUILabel` must implement
 this protocol.
 
 This protocol informs the keyboard when a particular `MTEditableMathUILabel` is being edited.
 The keyboard should use this information to send `UIKeyInput` messages to the label.
 
 This protocol inherits from `MTMathKeyboardTraits`.
 */
@protocol MTMathKeyboard <MTMathKeyboardTraits>

- (void) startedEditing:(id<UIKeyInput>) label;
- (void) finishedEditing:(id<UIKeyInput>) label;

@end


@interface MTEditableMathUILabel : UIView<UIKeyInput>

@property (nonatomic) MTMathList* mathList;
@property (nonatomic) UIColor* highlightColor;

@property (nonatomic) UIImageView* cancelImage;
@property (nonatomic, weak) id<MTEditableMathUILabelDelegate> delegate;
@property (nonatomic, weak) UIView<MTMathKeyboard>* keyboard;
@property (nonatomic) CGFloat fontSize;
@property (nonatomic) CGFloat paddingBottom;
@property (nonatomic) CGFloat paddingTop;

- (void) clear;

- (void) highlightCharacterAtIndex:(MTMathListIndex*) index;
- (void) clearHighlights;
- (void) moveCaretToPoint:(CGPoint) point;
- (void) startEditing;
- (void) enableTap:(BOOL) enable;

// Insert a list at a given point.
- (void) insertMathList:(MTMathList*) list atPoint:(CGPoint) point;

- (CGSize) mathDisplaySize;

@end
