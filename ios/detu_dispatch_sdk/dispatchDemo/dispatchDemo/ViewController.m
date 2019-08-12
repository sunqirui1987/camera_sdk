//
//  ViewController.m
//  dispatchDemo
//
//  Created by Seth on 17/3/2.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "ViewController.h"
#import "MainDispatcher.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
//    [[[MainDispatcher shareInstance] pushInpreview:^(Dispatch_Error_Type errorType, DispatchCommand command) {
//        Dispatch_Log(@"first ... ");
//        if (command == DispatchCommand_getCurrentMode) {
//            Dispatch_Log(@"complete dispatchCommand: getCurrentMode");
//        }
//    }] then:^{
//        Dispatch_Log(@"then ... ");
//    }] ;;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
