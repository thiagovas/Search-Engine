// UFMG/DCC - Information Retrieval - Practical Work #1
// Chilkat tests. Alberto Ueda, 2016-03-21

#include <iostream>
#include <stdio.h>
#include "CkSpider.h"

void printChilkatQueues(CkSpider *spider) 
{            
    // Now list the URLs we spidered, and the outbound links accumulated.
    int i;
    CkString url;    
    printf("Spidered URLs:\n");
    for (i = 0; i < spider->get_NumSpidered(); i++)
    {
        spider->GetSpideredUrl(i, url);
        printf("\t%s\n",url.getString());
    }
    
    printf("Unspidered URLs (total:%d):\n", spider->get_NumUnspidered());
    for (i = 0; i < spider->get_NumUnspidered(); i++)
    {
        spider->GetUnspideredUrl(i, url);
        printf("\t%s\n",url.getString());
    }
    
    printf("Outbound Links Remaining in the List:\n");
    for (i = 0; i < spider->get_NumOutboundLinks(); i++)
    {
        spider->GetOutboundLink(i, url);
        printf("\t%s\n", url.getString());
    }
}

// Spider a site and collect outbound links.
void testSpider(void)
{
    CkSpider spider;    
    spider.Initialize("http://www.chilkatsoft.com"); // Try also: http://www.chilkatsoft.com/crawlStart.html    

    CkString lastUrl, lastTitle, html;
    
    int count = 0, MAX_ROUNDS = 20;
    while (spider.get_NumUnspidered() > 0 && count < MAX_ROUNDS)
    {
        // Download the next unspidered URL.
        spider.CrawlNext(); // [IR Practical Work: The parameter 'html' of the original code does not exist in C++ implementation of Chilkat]
        
        // Log the URLs and HTML title of each URL fetched.
        spider.get_LastUrl(lastUrl);
        spider.get_LastHtmlTitle(lastTitle);
        // spider.get_LastHtml(html); // HTML text
         
        printf("URL[%d]: %s\nTitle: %s\n\n", count, lastUrl.getString(), lastTitle.getString());
        count++;
    }
    
    // Now list the URLs we spidered, and the outbound links accumulated.
    printChilkatQueues(&spider);
}

//  The spider object crawls a single web site at a time.  As you'll see
//  in later examples, you can collect outbound links and use them to
//  crawl the web. For now, we'll simply spider 10 pages of chilkatsoft.com
void testSpiderDelay(void)
{
    CkSpider spider;
    spider.Initialize("www.chilkatsoft.com");

    //  Add the 1st URL:
    spider.AddUnspidered("http://www.chilkatsoft.com/");

    //  Begin crawling the site by calling CrawlNext repeatedly.
    std::cout << "2nd Test: Crawling with Delay: " << "\n\n";
    int i;
    for (i = 0; i <= 9; i++) {
        bool success;
        success = spider.CrawlNext();
        if (success == true) {
            //  Show the URL of the page just spidered.
            std::cout << spider.lastUrl() << "\r\n";
            //  The HTML is available in the LastHtml property
        }
        else {
            //  Did we get an error or are there no more URLs to crawl?
            if (spider.get_NumUnspidered() == 0) {
                std::cout << "No more URLs to spider" << "\r\n";
            }
            else {
                std::cout << spider.lastErrorText() << "\r\n";
            }
        }

        //  Sleep 1 second before spidering the next URL.
        spider.SleepMs(1000);
    }
}

void testSpiderQueue(void)
{
    CkSpider spider;    
    spider.Initialize("http://www.chilkatsoft.com/support.asp");     
    
    printf("==================== ROUND 1 ====================\n");
    spider.CrawlNext();    
    printChilkatQueues(&spider);
    
    printf("==================== ROUND 2 ====================\n");            
    CkString nextUnspidered;    
    int i;
    // Clean the queue of unspidered links in order to gain control over it
    // [IR Practical Work: this way that queue always have exactly one element, which you choose.]    
    int total_unspidered = spider.get_NumUnspidered();
    for (i = 0; i < total_unspidered; i++)
    {    
        spider.GetUnspideredUrl(0, nextUnspidered);
        spider.SkipUnspidered(0); // Move the link to the queue of spidered links
        printf("---> Moving Unspidered URL [%s]...\n", nextUnspidered.getString());
                    
        // [IR Practical Work: Insert each nextUnspidered link in your priority queue]           
    }

    // [IR Practical Work: Finally add the first element of your priority queue as the next URL to be crawled]
    // [Replace the site below accordingly]
    spider.AddUnspidered("http://www.chilkatsoft.com/crawlstart.html");
    printChilkatQueues(&spider);
    
    printf("==================== ROUND 3 ====================\n");    
    spider.CrawlNext();    
    printChilkatQueues(&spider);
}

int main(int argc, char** argv)
{
    testSpider();
    testSpiderDelay();
    testSpiderQueue();
}
