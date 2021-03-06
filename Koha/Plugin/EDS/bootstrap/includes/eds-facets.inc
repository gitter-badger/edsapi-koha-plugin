<div id="search-facets">
    <h4><a href="#" class="menu-collapse-toggle">Refine your search</a></h4>
    <ul class="menu-collapse">
        <li id="availability_facet">
			Current Search
			
			[% IF query %]
				<ul>
				<li>Search Term(s)</li>
				[% FOR searchQuery IN query %]
				  <li>
					<a href="[% searchQuery.RemoveAction %]"><input type="checkbox" checked onchange="window.location.href=($(this).parent().attr('href'));$(this).attr('disabled','disabled');" > [% searchQuery.Query.BooleanOperator %][% IF searchQuery.Query.FieldCode %], [% searchQuery.Query.FieldCode %][% END %] : <span id="searchTerm">[% searchQuery.Query.Term %]</span></a>
				  </li>
				[% END %]
				</ul>
			[% END %]
			
			
			[% IF filters %]
				<ul>
				<li>Limiters</li>
				[% FOR facetFilter IN filters %]
				[% FOR facetFilterItem IN facetFilter.FacetValuesWithAction %]
				  <li>
					<a href="[% facetFilterItem.RemoveAction %]"><input type="checkbox" checked onchange="window.location.href=($(this).parent().attr('href'));$(this).attr('disabled','disabled');" > [% facetFilterItem.FacetValue.Id %] : [% facetFilterItem.FacetValue.Value %]</a>
				  </li>
				[% END %]
				[% END %]
				</ul>
			[% END %]
			
        </li> [% #seperate search criteria and facets %]
		
		[% IF limiters %]
		<li>
		[% IF limiters and expanders %]
		Limiters & Expanders
		[% ELSE %]
			[%IF limiters %]
				Limiters
			[% ELSE %]
				Expanders
			[% END %]
		[% END %]
			<ul>
				<li>Limit To:</li>
				[% FOR EDSLimit IN limiters %]
					[% IF EDSLimit.Type =='select' %]
						  <li>
							<a href="[% EDSLimit.AddAction %]">[% EDSLimit.Label %] </a>
						  </li>
					[% END %]
				[% END %]
			</ul>
			[% FOR EDSLimit IN limiters %][% IF EDSLimit.Type =='ymrange' %]
				<ul>
					<li>[% EDSLimit.Label %] 
						[% IF EDSLimit.DateValue %]
							<input title="Enter a date range and press Enter or clear this textbox to remove the date limiter." type="text" onkeypress="DateHandleKeyPress(event,this)" style="text-align:center;width:90%;" placeholder="YYYY-MM/YYYY-MM" value="[% EDSLimit.DateValue %]" >
						[% ELSE %]
							<input title="Enter a date range and press Enter or clear this textbox to remove the date limiter." type="text" onkeypress="DateHandleKeyPress(event,this)" style="text-align:center;width:90%;" placeholder="YYYY-MM/YYYY-MM" >
						[% END %]
						[% #action=removelimiter(DT1) %]
						<script>
						function DateHandleKeyPress(e,searchBox){
							var key=e.keyCode || e.which;
							if (key==13){
								var dateAction = "[% EDSLimit.AddAction %]";
								if(searchBox.value==""){
									dateAction= dateAction.replace('action=addlimiter(DT1:value)','action=removelimiter(DT1)');
									window.location.href=dateAction;
								}else{
									var regex = /^\d{4}-(0[1-9]|1[012])\/\d{4}-(0[1-9]|1[012])$/; 
									// '/\d{4}-\d[1-12]\/\d{4}-\d[1-12]/; - old'
									if(regex.test(searchBox.value)){
										dateAction= dateAction.replace('DT1:value','DT1:'+searchBox.value);
										window.location.href=dateAction;
									}else{alert('Invalid date. Please enter a date value in YYYY-MM/YYYY-MM format.\n e.g. 1900-01/2000-12.\n Remove all characters and hit enter to remove the date limiter.');}

								}
							}
						}
						</script>
					</li>
				</ul>
			[% END %][% END %]
			[% IF expanders %]
				<ul>
					<li>Expand To:</li>
					[% FOR expander IN expanders %]
					  <li>
						<a href="[% expander.AddAction %]">[% expander.Label %] </a>
					  </li>
					[% END %]
				</ul>
			[% END %]
			
        </li> [% #seperate limit and search criteria %]
		[% END %]
		
      [% FOR facets IN facets_loop %]
        <li>
          [% facets.Label %]
          <div style="max-height:200px;overflow:auto;margin:3px;">
			  <ul>
				[% FOR FacetValues IN facets.AvailableFacetValues %]
				  <li>
                  	<input type="checkbox" name="filter[]" value="" onChange="SetFacet(this);"> 
					<a href="[% FacetValues.AddAction %]">[% FacetValues.Value %]</a> ([% FacetValues.Count %])
				  </li>
				[% END %]
			  </ul>
		  </div>
        </li>
      [% END %]
	  
	  
    </ul>
</div>

[% IF ( OPACResultsSidebar ) %]
	<div id="opacresultssidebar">
		[% OPACResultsSidebar %]
	</div>
[% END %]