//
//  DejalUtilityDefines.h
//  Dejal Open Source
//
//  Created by David Sinclair on Sat May 07 2005.
//  Copyright (c) 2002-2015 Dejal Systems, LLC. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification,
//  are permitted provided that the following conditions are met:
//  
//  Redistributions of source code must retain this list of conditions and the following disclaimer.
//  
//  The name of Dejal Systems, LLC may not be used to endorse or promote products derived from this
//  software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//  PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
//  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THIS SOFTWARE.
//


// Global function defines:
#define sqr(x) pow(x,2)

#define DejalTestBit(flag, mask) ((flag & mask) == mask)
#define DejalSetBit(flag, mask, value) flag = value ? flag | mask : flag & ~mask

#define DejalSmaller(first, second) ((first < second) ? first : second)
#define DejalBigger(first, second) ((first > second) ? first : second)

#define DejalClassAvailable(className) (NSClassFromString(className) != nil)
#define DejalClassSelectorAvailable(className, selector) (NSClassFromString(className) != nil && [NSClassFromString(className) respondsToSelector:selector])

#define DejalDoubleClickInterval ([NSEvent doubleClickInterval] / 60.0)
#define DejalDoubleClickWithSlopInterval (([NSEvent doubleClickInterval] / 60.0) + 0.1)

// Convert minutes, hours, days, etc into a NSTimeInterval (seconds):
#define DejalIntervalFromMinutes(minutes) ((minutes) * 60.0)
#define DejalIntervalFromHours(hours) ((hours) * 3600.0)
#define DejalIntervalFromDays(days) ((days) * 86400.0)
#define DejalIntervalFromWeeks(weeks) ((weeks) * 604800.0)
#define DejalIntervalFromMonths(months) ((months) * 2628000.0)
#define DejalIntervalFromYears(years) ((years) * 31536000.0)

// Convert a NSTimeInterval (seconds) into minutes, hours, days, etc:
#define DejalMinutesFromInterval(seconds) ((seconds) / 60.0)
#define DejalHoursFromInterval(seconds) ((seconds) / 3600.0)
#define DejalDaysFromInterval(seconds) ((seconds) / 86400.0)
#define DejalWeeksFromInterval(seconds) ((seconds) / 604800.0)
#define DejalMonthsFromInterval(seconds) ((seconds) / 2628000.0)
#define DejalYearsFromInterval(seconds) ((seconds) / 31536000.0)

// Get just the file name from the compiler-defined __FILE__ value:
#define DEJAL_FILE_NAME ((strrchr(__FILE__, '/') ?: __FILE__ - 1) + 1)

// Get the date and time that the source code was compiled:
#define DEJAL_COMPILE_DATE_TIME ([NSString stringWithFormat:@"%s %s", __DATE__, __TIME__])

#define DejalWeakSelf __weak __typeof(self)

// Seeds the random values.  Call this before calling DejalRandomRange for the first time (okay to call again, too):
static inline void DejalRandomSeed()
{
    NSDateComponents *components = [[NSCalendar currentCalendar] components:(NSCalendarUnitDay | NSCalendarUnitMinute | NSCalendarUnitSecond) fromDate:[NSDate date]];
    NSUInteger randomValue = ([components day] * [components minute]) / ([components second] + 5);
    srandom((unsigned int)randomValue);
}

// Returns a random number between first and last, inclusive (couldn't do as define, as the compiler gave an error if the divisor was in the same line).  Note: should call DejalRandomSeed() at least once before this to seed the random values:
static inline NSInteger DejalRandomRange(NSInteger first, NSInteger last)
{
    NSInteger divisor = last - first + 1;
    
    return (random() % divisor) + first;
}

// Check if any object is empty:
static inline BOOL DejalIsEmpty(id object)
{
    return (object == nil) ||
        ([object respondsToSelector:@selector(length)] && [(NSData *)object length] == 0) ||
        ([object respondsToSelector:@selector(count)] && [(NSArray *)object count] == 0);
}

// Check if any object is not empty (similar to the -dejal_containsSomething category methods):
static inline BOOL DejalContainsSomething(id object)
{
    return ([object respondsToSelector:@selector(length)] && [(NSData *)object length] > 0) ||
        ([object respondsToSelector:@selector(count)] && [(NSArray *)object count] > 0) ||
        (object != nil);
}

// Returns "yes" if the condition is true, otherwise "no". Useful for debug descriptions.
static inline NSString *DejalYesNo(BOOL condition)
{
    return condition ? @"yes" : @"no";
}

// Returns YES if this application is an agent, i.e. a menu-less background helper app:
static inline BOOL DejalIsAgent()
{
    return ([[[NSBundle mainBundle] infoDictionary][@"NSUIElement"] boolValue]);
}


// Global debugging defines; put in the same scope to measure how long a block takes to execute:
#define DejalProfilerBegin(name) { NSString *__DejalProfilerName = name; \
    NSDate *__DejalProfilerStartDate = [NSDate date]; \
        NSLog(@"PROFILER: %@ started", __DejalProfilerName);
    
#define DejalProfilerEnd NSTimeInterval __DejalProfilerInterval = -[__DejalProfilerStartDate timeIntervalSinceNow]; \
    NSLog(@"PROFILER: %@ ended: total time %.4f seconds", __DejalProfilerName, __DejalProfilerInterval); }

// DEJALDEBUG should be defined in the OTHER_CFLAGS of the project for the Debug build configuration (set to -DEJALDEBUG=1):
#ifdef DEJALDEBUG
#    define DejalLog(...) NSLog(__VA_ARGS__)
#else
#    define DejalLog(...) /* */
#endif

