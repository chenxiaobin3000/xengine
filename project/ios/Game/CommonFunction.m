//
//  CommonFunction.m
//  Game
//
//  Created by chenxiaobin on 15/11/18.
//  Copyright © 2015年 xe. All rights reserved.
//

#import "CommonFunction.h"

@implementation CommonFunction

+ (NSString*)getWritePath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return documentsDirectory;
}

@end
