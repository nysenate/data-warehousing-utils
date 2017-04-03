survey-bill-alias 	sba	Run Survey of Bill Url Aliases.

alias-duplicates	adu	Finds Duplicate URL Aliases.

remove-duplicates	rdu	Removes Duplicate URL Aliases.

alias-short-amendments	asa	Find short URL aliases for amendments.

remove-alias-short-amendments   rasa remove-alias-short-amendments

alias-not-original	ano	Find the original outdated url aliass.

remove-not-original	rno	Remove the original outdated url aliass.

alias-empty		amt	Remove short URL aliases for amendments.

audit-url-alias		aua	General Audit of URL Aliases for Bills, Resolutions and Laws.

lookup-url-alias  lua   Show all the URL Aliases.

url-alias-report  uar   General Audit of URL Aliases for Bills, Resolutions and Laws.
                        Options:
                        --csv   This option makes the screen output csv instead of | and tab.
                        --sql   This option outputs the sql instead of the query results.

What Type Of Report Would You Like ?
 [0]   :  Cancel                                                          
 [1]   :  Base print_no Report                                            
 [2]   :  ammendment Report                                               
 [3]   :  print_no Report                                                 
 [4]   :  Working Well `url_alias_quantity` = `matched_alias` +           
          `matched_alias_amendment` Report                                
 [5]   :  Not Working (All) so well because `url_alias_quantity` !=       
          `matched_alias` + `matched_alias_amendment` Report              
 [6]   :  not Working (Regular aliases) Report                            
 [7]   :  not Working (Ammendment aliases) Report                         
 [8]   :  All Rows of the `nys_url_alias_audit` TABLE Report              
 [9]   :  All The Bill Aliases from the url_alias table Report            
 [10]  :  Quantity of aliases for each Base print_no using live data from 
          url_alias table Report                                          
 [11]  :  Describe `url_alias` Report                                     
 [12]  :  Describe `nys_url_alias_audit` Report



----------------------------------------------------------------------------
You need to run survey-bill-alias for some of these to run.


alias-short-amendments
Finds aliases like these
legislation/bills/2009/a10257a
legislation/bills/2009/a10257b
legislation/bills/2009/a10257c
legislation/bills/2009/a10257d


remove-alias-short-amendments
Removes aliases like these
legislation/bills/2009/a10257a
legislation/bills/2009/a10257b
legislation/bills/2009/a10257c
legislation/bills/2009/a10257d


alias-not-original
Finds Aliases like this
|  31054 | node/5016851 | legislation/bills/2009/a10257                    | und      |

remove-not-original
Removes older aliases like this
|  31054 | node/5016851 | legislation/bills/2009/a10257                    | und      |


And Leaves the newer Active Alias like this alone.
| 344599 | node/5016871 | legislation/bills/2009/A10257                    | und      |

