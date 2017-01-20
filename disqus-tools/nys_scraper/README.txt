NYS DISQUS SCRAPER


Has 4 drush commands

------------------------------------------------------------------------------------------
scrape-body-tags (sbd)

Shows the contents of the rewrite table that are not in the nys_disqus_scrape_data_raw table.


------------------------------------------------------------------------------------------
scrape-body-tags-1 (sbd1)

For every row in the nys_disqus_scrape_data_raw table.
  Get the node id by scraping the html of the page.
  Store the resulys in the nys_disqus_scrape_data table.


------------------------------------------------------------------------------------------
scrape-body-tags-2 (sbd2)

For each row in the nys_disqus_scrape_data table.

  Get the thread data using the disqus api.
  
  Inserts the link for the thread in nys_disqus_scrape_data_output table.

------------------------------------------------------------------------------------------
scrape-body-tags-3 (sbd3)

Surveys the nys_disqus_scrape_data_raw table.


------------------------------------------------------------------------------------------


