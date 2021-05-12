################################################################################################
# SDDL-Converter.ps1
# 
# AUTHOR: Robin Granberg (robin.granberg@microsoft.com)
#
# THIS CODE-SAMPLE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED 
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR 
# FITNESS FOR A PARTICULAR PURPOSE.
#
# This sample is not supported under any Microsoft standard support program or service. 
# The script is provided AS IS without warranty of any kind. Microsoft further disclaims all
# implied warranties including, without limitation, any implied warranties of merchantability
# or of fitness for a particular purpose. The entire risk arising out of the use or performance
# of the sample and documentation remains with you. In no event shall Microsoft, its authors,
# or anyone else involved in the creation, production, or delivery of the script be liable for 
# any damages whatsoever (including, without limitation, damages for loss of business profits, 
# business interruption, loss of business information, or other pecuniary loss) arising out of 
# the use of or inability to use the sample or documentation, even if Microsoft has been advised 
# of the possibility of such damages.
################################################################################################
<#-------------------------------------------------------------------------------
!! Version 1.0
April, 2018


-------------------------------------------------------------------------------#> 

Param
(
    )

begin
{
$null = Add-Type -AssemblyName System.DirectoryServices.Protocols
#==========================================================================
# Function		: ConvertGUID
# Arguments     : Object Guid or Rights Guid
# Returns   	: AD Searchable GUID String
# Description   : Convert a GUID to a string

#==========================================================================
Function ConvertGUID
 {
    Param($guid)

	 $test = "(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})"
	 $pattern = '"\$4\$3\$2\$1\$6\$5\$8\$7\$9\$10\$11\$12\$13\$14\$15\$16"'
	 $ConvertGUID = [regex]::Replace($guid.replace("-",""), $test, $pattern).Replace("`"","")
	 return $ConvertGUID
}
Function BuildSchemaDic
{

$global:dicSchemaIDGUIDs = @{"BF967ABA-0DE6-11D0-A285-00AA003049E2" ="user";`
"BF967A86-0DE6-11D0-A285-00AA003049E2" = "computer";`
"BF967A9C-0DE6-11D0-A285-00AA003049E2" = "group";`
"BF967ABB-0DE6-11D0-A285-00AA003049E2" = "volume";`
"F30E3BBE-9FF0-11D1-B603-0000F80367C1" = "gPLink";`
"F30E3BBF-9FF0-11D1-B603-0000F80367C1" = "gPOptions";`
"BF967AA8-0DE6-11D0-A285-00AA003049E2" = "printQueue";`
"4828CC14-1437-45BC-9B07-AD6F015E5F28" = "inetOrgPerson";`
"5CB41ED0-0E4C-11D0-A286-00AA003049E2" = "contact";`
"BF967AA5-0DE6-11D0-A285-00AA003049E2" = "organizationalUnit";`
"BF967A0A-0DE6-11D0-A285-00AA003049E2" = "pwdLastSet"}


$global:dicNameToSchemaIDGUIDs = @{"user"="BF967ABA-0DE6-11D0-A285-00AA003049E2";`
"computer" = "BF967A86-0DE6-11D0-A285-00AA003049E2";`
"group" = "BF967A9C-0DE6-11D0-A285-00AA003049E2";`
"volume" = "BF967ABB-0DE6-11D0-A285-00AA003049E2";`
"gPLink" = "F30E3BBE-9FF0-11D1-B603-0000F80367C1";`
"gPOptions" = "F30E3BBF-9FF0-11D1-B603-0000F80367C1";`
"printQueue" = "BF967AA8-0DE6-11D0-A285-00AA003049E2";`
"inetOrgPerson" = "4828CC14-1437-45BC-9B07-AD6F015E5F28";`
"contact" = "5CB41ED0-0E4C-11D0-A286-00AA003049E2";`
"organizationalUnit" = "BF967AA5-0DE6-11D0-A285-00AA003049E2";`
"pwdLastSet" = "BF967A0A-0DE6-11D0-A285-00AA003049E2"}
}
BuildSchemaDic
#==========================================================================
# Function		: CacheRightsGuids
# Arguments     : none
# Returns   	: nothing
# Description   : Enumerates all Extended Rights and put them in a Hash dicRightsGuids
#==========================================================================
Function CacheRightsGuids
{
	
        
        $LDAPConnection = New-Object System.DirectoryServices.Protocols.LDAPConnection($global:strDC, $global:CREDS)
        $LDAPConnection.SessionOptions.ReferralChasing = "None"
        $searcher = New-Object System.directoryServices.Protocols.SearchRequest
        $searcher.DistinguishedName = $global:ConfigDN

        [void]$searcher.Attributes.Add("cn")
        [void]$searcher.Attributes.Add("name")                        
        [void]$searcher.Attributes.Add("rightsguid")
        [void]$searcher.Attributes.Add("validaccesses")
        [void]$searcher.Attributes.Add("displayname")
		$searcher.filter = "(&(objectClass=controlAccessRight))"

        $searcherSent = $LDAPConnection.SendRequest($searcher)
        $colResults = $searcherSent.Entries        
 		$intCounter = 0
	
	foreach ($objResult in $colResults)
	{

		    $strRightDisplayName = $objResult.Attributes.displayname[0]
		    $strRightGuid = $objResult.Attributes.rightsguid[0]
		    $strRightGuid = $($strRightGuid).toString()

            #Expecting to fail at lest once since two objects have the same rightsguid
            &{#Try

		        $global:dicRightsGuids.Add($strRightGuid,$strRightDisplayName)	
            }
            Trap [SystemException]
            {
                #Write-host "Failed to add CAR:$strRightDisplayName" -ForegroundColor red
                continue
            }

		$intCounter++
    }
			 

}
#==========================================================================
# Function		: Get-DirContext 
# Arguments     : string domain controller,credentials
# Returns   	: Directory context
# Description   : Get Directory Context
#==========================================================================
function Get-DirContext
{
Param($DomainController,
[System.Management.Automation.PSCredential] $DIRCREDS)

	if($global:CREDS)
		{
		$Context = new-object DirectoryServices.ActiveDirectory.DirectoryContext("DirectoryServer",$DomainController,$DIRCREDS.UserName,$DIRCREDS.GetNetworkCredential().Password)
	}
	else
	{
		$Context = New-Object DirectoryServices.ActiveDirectory.DirectoryContext("DirectoryServer",$DomainController)
	}
	

    return $Context
}
#==========================================================================
# Function		: GetDomainShortName
# Arguments     : domain name 
# Returns   	: N/A
# Description   : Search for short domain name
#==========================================================================
function GetDomainShortName
{ 
Param($strDomain,
[string]$strConfigDN)

    $LDAPConnection = New-Object System.DirectoryServices.Protocols.LDAPConnection($global:strDC, $global:CREDS)
    $LDAPConnection.SessionOptions.ReferralChasing = "None"
    $request = New-Object System.directoryServices.Protocols.SearchRequest("CN=Partitions,$strConfigDN", "(&(objectClass=crossRef)(nCName=$strDomain))", "Subtree")
    [void]$request.Attributes.Add("netbiosname")
    $response = $LDAPConnection.SendRequest($request)
    $adObject = $response.Entries[0]

    if($null -ne $adObject)
    {

        $ReturnShortName = $adObject.Attributes.netbiosname[0]
	}
	else
	{
		$ReturnShortName = ""
	}
 
return $ReturnShortName
}
$LDAPConnection = $null
$request = $null
$response = $null
$LDAPConnection = New-Object System.DirectoryServices.Protocols.LDAPConnection("")
$LDAPConnection.SessionOptions.ReferralChasing = "None"
$request = New-Object System.directoryServices.Protocols.SearchRequest($null, "(objectClass=*)", "base")
[void]$request.Attributes.Add("defaultnamingcontext")
try
{
    $response = $LDAPConnection.SendRequest($request)
    $global:strDomainDNName = $response.Entries[0].Attributes.defaultnamingcontext[0]
    $global:bolLDAPConnection = $true
}
catch
{
	$global:bolLDAPConnection = $false
    #Write-Error "Failed! Domain does not exist or can not be connected" 
}

if($global:bolLDAPConnection)
{
    $global:strDomainPrinDNName = $global:strDomainDNName
    $global:strDomainLongName = $global:strDomainDNName.Replace("DC=","")
    $global:strDomainLongName = $global:strDomainLongName.Replace(",",".")
    $Context = New-Object DirectoryServices.ActiveDirectory.DirectoryContext("Domain",$global:strDomainLongName )
    $ojbDomain = [DirectoryServices.ActiveDirectory.Domain]::GetDomain($Context)
    $global:strDC = $($ojbDomain.FindDomainController()).name
    $LDAPConnection = New-Object System.DirectoryServices.Protocols.LDAPConnection($global:strDC, $global:CREDS)
    $LDAPConnection.SessionOptions.ReferralChasing = "None"
    $request = New-Object System.directoryServices.Protocols.SearchRequest($null, "(objectClass=*)", "base")
    [void]$request.Attributes.Add("dnshostname")
    [void]$request.Attributes.Add("supportedcapabilities")
    [void]$request.Attributes.Add("namingcontexts")
    [void]$request.Attributes.Add("defaultnamingcontext")
    [void]$request.Attributes.Add("schemanamingcontext")
    [void]$request.Attributes.Add("configurationnamingcontext")
    [void]$request.Attributes.Add("rootdomainnamingcontext")
    [void]$request.Attributes.Add("isGlobalCatalogReady")
                    
    try
    {
        $response = $LDAPConnection.SendRequest($request)
        $global:bolLDAPConnection = $true
    }
    catch
    {
    	$global:bolLDAPConnection = $false
        Write-Error "Failed! Domain does not exist or can not be connected" 
    }
    if($global:bolLDAPConnection -eq $true)
    {
        $global:ForestRootDomainDN = $response.Entries[0].attributes.rootdomainnamingcontext[0]
        $global:SchemaDN = $response.Entries[0].attributes.schemanamingcontext[0]
        $global:ConfigDN = $response.Entries[0].attributes.configurationnamingcontext[0]
        $global:strDomainDNName = $response.Entries[0].attributes.defaultnamingcontext[0]
        $global:IS_GC = $response.Entries[0].Attributes.isglobalcatalogready[0]

        $global:dicRightsGuids = @{"Seed" = "xxx"}
	    CacheRightsGuids
    }

    $global:DirContext = Get-DirContext $global:strDC $global:CREDS
    $global:strDomainShortName = GetDomainShortName $global:strDomainDNName $global:ConfigDN
    $global:strRootDomainShortName = GetDomainShortName $global:ForestRootDomainDN $global:ConfigDN
    $global:DSType = "AD DS"
    $global:bolADDSType = $true
    $NCSelect = $true
    $strNamingContextDN = $global:strDomainDNName
}
#==========================================================================
# Function		: MapGUIDToMatchingName
# Arguments     : Object Guid or Rights Guid
# Returns   	: LDAPDisplayName or DisplayName
# Description   : Searches in the dictionaries(Hash) dicRightsGuids and $global:dicSchemaIDGUIDs  and in Schema 
#				for the name of the object or Extended Right, if found in Schema the dicRightsGuids is updated.
#				Then the functions return the name(LDAPDisplayName or DisplayName).
#==========================================================================
Function MapGUIDToMatchingName
{
Param([string] $strGUIDAsString,[string] $Domain)
	[string] $strOut = $strGUIDAsString
	[string] $strLDAPname = ""

    If ($strGUIDAsString -eq "") 
    {
        Break
    }
	$strGUIDAsString = $strGUIDAsString.toUpper()

	if ($global:dicRightsGuids.ContainsKey($strGUIDAsString))
	{
		$strOut =$global:dicRightsGuids.Item($strGUIDAsString)
	}

	If ($strOut -eq $strGUIDAsString)
	{  #Didn't find a match in extended rights
		If ($global:dicSchemaIDGUIDs.ContainsKey($strGUIDAsString))
		{
			$strOut =$global:dicSchemaIDGUIDs.Item($strGUIDAsString)
		}
		else
		{
		
		 if ($strGUIDAsString -match("^(\{){0,1}[0-9a-fA-F]{8}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{12}(\}){0,1}$"))
		 {
		 	
			$ConvertGUID = ConvertGUID($strGUIDAsString)
		    if($global:bolLDAPConnection)        
            {
                $LDAPConnection = New-Object System.DirectoryServices.Protocols.LDAPConnection($global:strDC, $global:CREDS)
                $LDAPConnection.SessionOptions.ReferralChasing = "None"
                $searcher = New-Object System.directoryServices.Protocols.SearchRequest
                $searcher.DistinguishedName = $global:SchemaDN

                [void]$searcher.Attributes.Add("cn")
    
                [void]$searcher.Attributes.Add("name")                        
                [void]$searcher.Attributes.Add("ldapdisplayname")
			    $searcher.filter = "(&(schemaIDGUID=$ConvertGUID))"

                $searcherSent = $LDAPConnection.SendRequest($searcher)
                $objSchemaObject = $searcherSent.Entries[0]

			     if ($objSchemaObject)
			     {
				    $strLDAPname =$objSchemaObject.attributes.ldapdisplayname[0]
				    $global:dicSchemaIDGUIDs.Add($strGUIDAsString.toUpper(),$strLDAPname)
				    $strOut=$strLDAPname
				
			     }
            }
		}
	  }
	}
    
	return $strOut
}

function WriteOUT
{
    Param($sd)
$ArrayAllACE = New-Object System.Collections.ArrayList

if($Type -eq "EXCEL")
{
$EXCEL = $true
$fileout = $xlsxout
}


$sd  | foreach{


if($null  -ne  $_.AccessControlType)
{
    $objAccess = $($_.AccessControlType.toString())
}
else
{
    $objAccess = $($_.AuditFlags.toString())
}
$objFlags = $($_.ObjectFlags.toString())
$objType = $($_.ObjectType.toString())
$objIsInheried = $($_.IsInherited.toString())
$objInheritedType = $($_.InheritedObjectType.toString())
$objRights = $($_.ActiveDirectoryRights.toString())
$objInheritanceType = $($_.InheritanceType.toString())
    


if($chkBoxEffectiveRightsColor.IsChecked -eq $false)
{
    Switch ($objRights)
    {
   		"Self"
    	{
            #Self right are never express in gui it's a validated write ( 0x00000008 ACTRL_DS_SELF)

                $objRights = ""
        }
    	"DeleteChild, DeleteTree, Delete"
    	{
    		$objRights = "DeleteChild, DeleteTree, Delete"

    	}
    	"GenericRead"
    	{
    		$objRights = "Read Permissions,List Contents,Read All Properties,List"
        }
    	"CreateChild"
    	{
    		$objRights = "Create"	
    	}
    	"DeleteChild"
    	{
    		$objRights = "Delete"		
    	}
    	"GenericAll"
    	{
    		$objRights = "Full Control"		
    	}
    	"CreateChild, DeleteChild"
    	{
    		$objRights = "Create/Delete"		
    	}
    	"ReadProperty"
    	{
    	    Switch ($objInheritanceType) 
    	    {
    	 	    "None"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                    default
    	 	                    {$objRights = "Read All Properties"	}
                            }#End switch



                    }
                                  	 	    "Children"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                    default
    	 	                    {$objRights = "Read All Properties"	}
                            }#End switch
                            }
                        	 	    "Descendents"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Read"	
                }
                    default
    	 	                    {$objRights = "Read All Properties"	}
                            }#End switch
                            }
    	 	    default
    	 	    {$objRights = "Read All Properties"	}
            }#End switch

    			           	
    	}
    	"ReadProperty, WriteProperty" 
    	{
    		$objRights = "Read All Properties;Write All Properties"			
    	}
    	"WriteProperty" 
    	{
    	    Switch ($objInheritanceType) 
    	    {
    	 	    "None"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                    default
    	 	                    {$objRights = "Write All Properties"	}
                            }#End switch



                    }
                                  	 	    "Children"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                    default
    	 	                    {$objRights = "Write All Properties"	}
                            }#End switch
                            }
                        	 	    "Descendents"
    	 	    {
                     
                        	 	Switch ($objFlags)
    	    	            { 
    		      	            "ObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                       	                
    		      	            "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                {
                    $objRights = "Write"	
                }
                    default
    	 	                    {$objRights = "Write All Properties"	}
                            }#End switch
                            }
    	 	    default
    	 	    {$objRights = "Write All Properties"	}
            }#End switch		
    	}
    }# End Switch
}
else
{
 
    Switch ($objRights)
    {
    	"Self"
    	{
            #Self right are never express in gui it's a validated write ( 0x00000008 ACTRL_DS_SELF)

                $objRights = ""
        }
    	"GenericRead"
    	{
                $objRights = "Read Permissions,List Contents,Read All Properties,List"
        }
    	"CreateChild"
    	{
                $objRights = "Create"	
    	}
    	"DeleteChild"
    	{
            $objRights = "Delete"		
    	}
    	"GenericAll"
    	{
            $objRights = "Full Control"		
    	}
    	"CreateChild, DeleteChild"
    	{
            $objRights = "Create/Delete"		
    	}
    	"ReadProperty"
    	{
            Switch ($objInheritanceType) 
    	    {
    	 	    "None"
    	 	    {
                     
                    Switch ($objFlags)
    	    	    { 
    		      	    "ObjectAceTypePresent"
                        {
                            $objRights = "Read"	
                        }
    		      	    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                            $objRights = "Read"	
                        }
                        default
    	 	            {$objRights = "Read All Properties"	}
                    }#End switch
                }
                    "Children"
    	 	    {
                     
                    Switch ($objFlags)
    	    	    { 
    		      	    "ObjectAceTypePresent"
                        {
                            $objRights = "Read"	
                        }
    		      	    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                            $objRights = "Read"	
                        }
                        default
    	 	            {$objRights = "Read All Properties"	}
                    }#End switch
                }
                "Descendents"
                {
                    Switch ($objFlags)
                    { 
                        "ObjectAceTypePresent"
                        {
                        $objRights = "Read"	
                        }
                       	                
                        "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                        $objRights = "Read"	
                        }
                        default
                        {$objRights = "Read All Properties"	}
                    }#End switch
                }
                default
                {$objRights = "Read All Properties"	}
            }#End switch
    	}
    	"ReadProperty, WriteProperty" 
    	{
            $objRights = "Read All Properties;Write All Properties"			
    	}
    	"WriteProperty" 
    	{
            Switch ($objInheritanceType) 
    	    {
    	 	    "None"
    	 	    {
                    Switch ($objFlags)
                    { 
                        "ObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        default
                        {
                            $objRights = "Write All Properties"	
                        }
                    }#End switch
                }
                "Children"
                {
                    Switch ($objFlags)
                    { 
                        "ObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        default
                        {
                            $objRights = "Write All Properties"	
                        }
                    }#End switch
                }
                "Descendents"
                {
                    Switch ($objFlags)
                    { 
                        "ObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        "ObjectAceTypePresent, InheritedObjectAceTypePresent"
                        {
                            $objRights = "Write"	
                        }
                        default
                        {
                            $objRights = "Write All Properties"	
                        }
                    }#End switch
                }
                default
                {
                    $objRights = "Write All Properties"
                }
            }#End switch		
    	}
        default
        {
  
        }
    }# End Switch  


        
}#End IF else

$IdentityReference = $($_.IdentityReference.toString())
    
If ($IdentityReference.contains("S-1-"))
{
	#$strNTAccount = ConvertSidToName -server $global:strDomainLongName -Sid $IdentityReference

}
else
{
    $strNTAccount = $IdentityReference 
}
   


Switch ($objInheritanceType) 
{
    "All"
    {
	    Switch ($objFlags) 
	    { 
		    "InheritedObjectAceTypePresent"
		    {
		        $strApplyTo =  "This object and all child objects"
                $strPerm =  "$objRights $(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
		    }    	
		    "ObjectAceTypePresent"
		    {
		        $strApplyTo =  "This object and all child objects"
                $strPerm =  "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 
		    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
		    {
		        $strApplyTo =  "$(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
                $strPerm =  "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 	      	
		    "None"
		    {
		        $strApplyTo ="This object and all child objects"
                $strPerm = "$objRights"
		    } 
		        default
	 	    {
		        $strApplyTo = "Error"
                $strPerm = "Error: Failed to display permissions 1K"
		    } 	 
	
	    }# End Switch
	 		
    }
    "Descendents"
    {
	
	    Switch ($objFlags)
	    { 
		    "InheritedObjectAceTypePresent"
		    {
		        $strApplyTo = "$(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
                $strPerm = "$objRights"
		    }
		    "None"
		    {
		        $strApplyTo = "Child Objects Only"
                $strPerm = "$objRights"
		    } 	      	
		    "ObjectAceTypePresent"
		    {
		        $strApplyTo = "Child Objects Only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 
		    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
		    {
		        $strApplyTo =	"$(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
                $strPerm =	"$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    }
		    default
	 	    {
		        $strApplyTo = "Error"
                $strPerm = "Error: Failed to display permissions 2K"
		    } 	 
	
	    } 		
    }
    "None"
    {
	    Switch ($objFlags)
	    { 
		    "ObjectAceTypePresent"
		    {
		        $strApplyTo = "This Object Only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 
		    "None"
		    {
		        $strApplyTo = "This Object Only"
                $strPerm = "$objRights"
		    } 
		        default
	 	    {
		        $strApplyTo = "Error"
                $strPerm = "Error: Failed to display permissions 4K"
		    } 	 
	
	    }
    }
    "SelfAndChildren"
    {
	 	    Switch ($objFlags)
	    { 
		    "ObjectAceTypePresent"
	        {
		        $strApplyTo = "This object and all child objects within this conatainer only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    }
		    "InheritedObjectAceTypePresent"
		    {
		        $strApplyTo = "Children within this conatainer only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
		    } 

		    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
		    {
		        $strApplyTo =  "$(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
                $strPerm =  "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 	      	
		    "None"
		    {
		        $strApplyTo = "This object and all child objects"
                $strPerm = "$objRights"
		    }                                  	   
		    default
	 	    {
		        $strApplyTo = "Error"
                $strPerm = "Error: Failed to display permissions 5K"
		    } 	 
	
	    }   	
    } 	
    "Children"
    {
	 	    Switch ($objFlags)
	    { 
		    "InheritedObjectAceTypePresent"
		    {
		        $strApplyTo = "Children within this conatainer only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
		    } 
		    "None"
		    {
		        $strApplyTo = "Children  within this conatainer only"
                $strPerm = "$objRights"
		    } 	      	
		    "ObjectAceTypePresent, InheritedObjectAceTypePresent"
	        {
		        $strApplyTo = "$(if($bolTranslateGUID){$objInheritedType}else{MapGUIDToMatchingName -strGUIDAsString $objInheritedType -Domain $global:strDomainDNName})"
                $strPerm = "$(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName}) $objRights"
		    } 	
		    "ObjectAceTypePresent"
	        {
		        $strApplyTo = "Children within this conatainer only"
                $strPerm = "$objRights $(if($bolTranslateGUID){$objType}else{MapGUIDToMatchingName -strGUIDAsString $objType -Domain $global:strDomainDNName})"
		    } 		      	
		    default
	 	    {
		        $strApplyTo = "Error"
                $strPerm = "Error: Failed to display permissions 6K"
		    } 	 
	
	    }
    }
    default
    {
	    $strApplyTo = "Error"
        $strPerm = "Error: Failed to display permissions 7K"
    } 	 
}# End Switch

##

$objhashtableACE = [pscustomobject][ordered]@{IdentityReference = $IdentityReference ;`Trustee = $strNTAccount ;`Access = $objAccess ;`
Inhereted = $objIsInheried ;`
ApplyTo = $strApplyTo ;`
Permission = $strPerm}

if($boolReplMetaDate)
{
    $objhashtableACE | Add-Member NoteProperty "Security Descriptor Modified" $strReplMetaDate -PassThru 
}

if($CompareMode)
{
    $objhashtableACE | Add-Member NoteProperty State $($_.State.toString()) -PassThru 
}
[VOID]$ArrayAllACE.Add($objhashtableACE)



}# End Foreach

Return $ArrayAllACE

}


#Load Presentation Framework
Add-Type -Assembly PresentationFramework



$xamlBase =@"
<Window x:Class="WpfApplication1.SDDLTOACL"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:WpfApplication1"

        Title="SDDL-Converter" WindowStartupLocation="CenterScreen" Height="500" Width="1023" ResizeMode="CanResizeWithGrip" WindowState="Maximized"  >
        <ScrollViewer HorizontalScrollBarVisibility="Auto" VerticalScrollBarVisibility="Auto">
        <Grid Background="white">
        <StackPanel Orientation="Vertical" >
        <Label x:Name="lblAuthor" Margin="0,0,0,0"  Content="Author: robingra@microsoft.com"  HorizontalAlignment="Right" VerticalAlignment="Bottom" Foreground="#000000"/>
        <Label x:Name="lblXPath" Margin="0,0,0,0"  Content="Paste your SDDL String here:" FontWeight="Bold"  FontSize="14"  HorizontalAlignment="LEft" Foreground="#000000"/>
        <TextBox x:Name="txtBoxSDDL" Margin="0,0,0,0"  Text="" FontWeight="Normal" Width="900" Height="150" FontSize="14"  HorizontalAlignment="LEft" Foreground="#FF0000" TextWrapping="WrapWithOverflow" AcceptsReturn="True" />
        <StackPanel Orientation="Horizontal" >
        <Button x:Name="btnExit" Content="Exit" HorizontalAlignment="Center" Margin="50,0,0,0" VerticalAlignment="Top" Width="75"/>
        <Button x:Name="btnRun" Content="Run" HorizontalAlignment="Center" Margin="50,0,0,0" VerticalAlignment="Top" Width="75"/>
        </StackPanel>
        <Label x:Name="lblSD" Margin="0,0,0,0"  Content="Security Descriptor:" FontWeight="Bold"   FontSize="14"  HorizontalAlignment="LEft" Foreground="#000000"/>
            <DataGrid Name="dgSD" HorizontalAlignment="Left" Margin="0,0,0,10" Width="750"  MaxHeight="350" GridLinesVisibility="None" AlternationCount="2" IsReadOnly="True" FontSize="14">
            <DataGrid.ColumnHeaderStyle>
                    <Style TargetType="Control">
                    <Setter Property="FontWeight" Value="Bold"/>
                </Style>
            </DataGrid.ColumnHeaderStyle>
            <DataGrid.Columns>
                <DataGridTextColumn Header='Path' Binding='{Binding Path}' Width='120' />
                <DataGridTextColumn Header='Owner' Binding='{Binding Owner}' Width='190' />
                <DataGridTextColumn Header='Group' Binding='{Binding Group}' Width='190' />
                <DataGridTextColumn Header='DACL Protected ' Binding='{Binding AreAccessRulesProtected }' Width='120' />
                <DataGridTextColumn Header='SACL Protected ' Binding='{Binding AreAuditRulesProtected  }' Width='120' />
                <DataGridTextColumn Header='DACL Canonical ' Binding='{Binding AreAccessRulesCanonical }' Width='120' />
                <DataGridTextColumn Header='SACL Canonical ' Binding='{Binding AreAuditRulesCanonical }' Width='120' />
              </DataGrid.Columns>
            </DataGrid>
        <Label x:Name="lblACL" Margin="0,0,0,0"  Content="ACL:" FontWeight="Bold"   FontSize="14"  HorizontalAlignment="LEft" Foreground="#000000"/>
            <DataGrid Name="dgACEs" HorizontalAlignment="Left" Margin="0,0,0,10" Width="750"  MaxHeight="350" GridLinesVisibility="None" AlternationCount="2" AlternatingRowBackground="LightBlue" IsReadOnly="True" FontSize="14">
            <DataGrid.ColumnHeaderStyle>
                    <Style TargetType="Control">
                    <Setter Property="FontWeight" Value="Bold"/>
                </Style>
            </DataGrid.ColumnHeaderStyle>            
            <DataGrid.Columns>
                <DataGridTextColumn Header='IdentityReference' Binding='{Binding IdentityReference}' Width='SizeToCells' />
                <DataGridTextColumn Header='Trustee' Binding='{Binding Trustee}' Width='SizeToCells' />
                <DataGridTextColumn Header='Access' Binding='{Binding Access}' Width='SizeToCells' />
                <DataGridTextColumn Header='ApplyTo' Binding='{Binding ApplyTo }' Width='SizeToCells' />
                <DataGridTextColumn Header='Permission ' Binding='{Binding Permission }' Width='SizeToCells' />
              </DataGrid.Columns>
            </DataGrid>
        </StackPanel>
    </Grid>
    </ScrollViewer>
</Window>
"@




#Replace x:Name to XML variable Name
$xamlBase = $xamlBase.Replace("x:Name","Name")
[XML] $XAML = $xamlBase
$xaml.Window.RemoveAttribute("x:Class")  
  
$reader=(New-Object System.Xml.XmlNodeReader $XAML)
$Window=[Windows.Markup.XamlReader]::Load( $reader )

#Search the XML data for object and create variables
$XAML.SelectNodes("//*[@Name]")| %{set-variable -Name ($_.Name) -Value $Window.FindName($_.Name)}

}

Process
{
# Creating a filter with custom log name

$btnRun.add_Click({
    
    $bolFailure = $false

    #Clear Item from grid
    While ($dgSD.Items.count -gt 0)
    {
        $dgSD.Items.Remove($dgSD.Items[0])
    }

    #Clear Item from grid
    While ($dgACEs.Items.count -gt 0)
    {
        $dgACEs.Items.Remove($dgACEs.Items[0])
    }

    $secAD = New-Object System.DirectoryServices.ActiveDirectorySecurity

    $defSD = ""
    try
    {
        $secAD.SetSecurityDescriptorSddlForm($txtBoxSDDL.Text)
    }
    catch
    {
        $Msgox = [System.Windows.Forms.MessageBox]::Show("The SDDL form of a security descriptor object is invalid","Error",0,"Error")
        $bolFailure = $true
    }

    if(!($bolFailure))
    {
        $defSD =$secAD.GetAccessRules($true, $false, [System.Security.Principal.NTAccount])   
        $convertedSD = WriteOUT $defSD

        [void]$dgSD.AddChild($($secAD | select-object -Property Path,Owner,Group,AreAccessRulesProtected,AreAuditRulesProtected,AreAccessRulesCanonical,AreAuditRulesCanonical))

        Foreach ($ACE in $convertedSD)
        {
            [void]$dgACEs.AddChild($ACE)
        }
    }
})

$btnExit.add_Click( 
{
    $Window.close()
})
}
End
{
 
    if([System.Windows.SystemParameters]::PrimaryScreenWidth -gt $Window.Width)
    {
    $Window.Width =   [System.Windows.SystemParameters]::PrimaryScreenWidth
    $dgSD.Width = $([System.Windows.SystemParameters]::PrimaryScreenWidth - ([System.Windows.SystemParameters]::PrimaryScreenWidth * 0.02))
    $dgACEs.Width = $([System.Windows.SystemParameters]::PrimaryScreenWidth - ([System.Windows.SystemParameters]::PrimaryScreenWidth * 0.02))
    $txtBoxSDDL.Width = $([System.Windows.SystemParameters]::PrimaryScreenWidth - ([System.Windows.SystemParameters]::PrimaryScreenWidth * 0.02))
    }
    $Window.ShowDialog() | Out-Null


}

