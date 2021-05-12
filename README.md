
# Intro
The goal of Shutter is to manage windows network stack communication via Windows Filtering Platform. 
Management can include _blocking_ or _permiting_ traffic based on IP or an executable that initiates or receives the traffic.

This is useful to blackhole event logging, defensive agent communication, or explicitly permit specific executables to communicate if they have been previously restricted by policy. 

Shutter installs rules in a memory running session without touching the windows firewall itself or invocation of `netsh` command, thereby minimizing detection during long haul RT operations.

As a generic mechanism for managing network traffic it can help RTOs in:
- punching through firewalls without shutting them down
- not creating persistent rules 
- evading reporting on `netsh` invocation
- blackholing EDRs and activity supervising agents. 
- studying existing security providers, active filters and network endpoints involved in network communication

For now, IPv4 support is implemented, with or without applciation paths (see examples)

# Architecture

## Architecture diagram
![Architecture](Docs/images/ShutterArch.png ="500x400")

# Operations

- It needs to run elevated (due to WFP).
- Opsec - TBD

# Usage

```
C:\Temp\Shutter> C:\Temp\Shutter\x64\Debug\Appblock.exe --list --help
Block by condition
Usage:
  AppBlock [OPTION...] [--list | --add | --remove]

 general options:
  -h, --help     Print usage
  -v, --verbose  Verbose output
  -d, --debug    Enable debugging

 action options:
      --list    list
      --add     add
      --remove  remove

 qualifier options:
      --filter [=arg(=)]    list:filter GUID | add:filter file path
      --layer [=arg(=)]     layer
      --sublayer [=arg(=)]  sublayer
      --session [=arg(=)]   session
      --provider [=arg(=)]  provider
      --context [=arg(=)]   context
      --event               event

 result options:
      --output [=arg(=out.json)]
                                output
```

## Examples:

### List filtes, layers, providers,

- Hunt artifacts
- Assess defenses 
- Identified blocking policies


Extensive docs - TBD 


### Add filters via rules file
```
C:\Appblock.exe --add  --filter=add-filters-defender-crowdstrike.json

Installing Filter: Defense Sec Updates Filter
+ Key: A2F1A73B-D762-4A3E-B1EE-60BE052E754C
+ In Layer: C38D57D1-05A7-4C33-904F-7FBCEEE60E82(FWPM_LAYER_ALE_AUTH_CONNECT_V4)
C:\Program Files\Windows Defender\MsMpEng.exe
C:\Program Files\Windows Defender\NisSrv.exe
C:\Program Files\Windows Defender\ConfigSecurityPolicy.exe
C:\Program Files\Windows Defender\MpCmdRun.exe

Installing Filter: WinDefender Filter
+ Key: A1F1A73B-E762-4A3E-B1EE-60BE052E754C
+ In Layer: C38D57D1-05A7-4C33-904F-7FBCEEE60E82(FWPM_LAYER_ALE_AUTH_CONNECT_V4)
C:\Program Files\Windows Defender Advanced Threat Protection\MsSense.exe
C:\Program Files\Windows Defender Advanced Threat Protection\SenseCncProxy.exe
C:\Program Files\Windows Defender Advanced Threat Protection\SenseIR.exe
C:\Program Files\Windows Defender Advanced Threat Protection\SenseNdr.exe
C:\Program Files\Windows Defender Advanced Threat Protection\SenseSampleUploader.exe
C:\Program Files\Windows Defender Advanced Threat Protection\SenseSC.exe

Installing Filter: WinDefender AMSI Filter
+ Key: B1F1A73B-E762-4A3E-B1EE-60BE052E754D
+ In Layer: C38D57D1-05A7-4C33-904F-7FBCEEE60E82(FWPM_LAYER_ALE_AUTH_CONNECT_V4)
C:\Program Files\CrowdStrike\CSCOMUtils.exe
C:\Program Files\CrowdStrike\CSDeviceControlSupportTool.exe
C:\Program Files\CrowdStrike\CSFalconContainer.exe
C:\Program Files\CrowdStrike\CSFalconController.exe
C:\Program Files\CrowdStrike\CSFalconService.exe
```

### Rules file

```
{
    "Meta": {
      "SubLayerName": "Shutter SL",
      "SubLayerWeight": 65535
    },
    "Filters": [
       {
          "FilterAction": "FWP_ACTION_BLOCK",
          "FilterType": "APP",
          "FilterConditions": [
            // Defender definitions updates
            { "DataValue": "23.53.112.109", "MatchType": "EQUAL", "DataType": "IPADDR" },

            // Rapid7 updates
            { "DataValue": "52.203.25.223", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "54.144.111.231", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "34.226.68.35", "MatchType": "EQUAL", "DataType": "IPADDR" },

            // Defender SmartScreen submission wdcp.microsoft.com and wdcpalt.microsoft.com
            { "DataValue": "40.76.203.101", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "40.78.1.30", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "13.82.144.201", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "23.101.202.202", "MatchType": "EQUAL", "DataType": "IPADDR" },

            // smartscreen.microsoft.com martscreen-prod.microsoft.com and checkappexec.microsoft.com 
            { "DataValue": "157.55.163.108", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "13.68.247.210", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "104.214.58.194", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "104.42.196.205", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "104.42.54.233", "MatchType": "EQUAL", "DataType": "IPADDR" },
            { "DataValue": "70.37.97.229", "MatchType": "EQUAL", "DataType": "IPADDR" },

            // MSFT NCSI 
            { "DataValue": "13.107.4.52", "MatchType": "EQUAL", "DataType": "IPADDR" }


          ],
          "FilterKey": "A2F1A73B-D762-4A3E-B1EE-60BE052E754C",
          "FilterName": "Defense Sec Updates Filter",
          "FilterDesc": "Defense Sec Updates - block outgoing",
          "FilterLayerName": "FWPM_LAYER_ALE_AUTH_CONNECT_V4",
          "FilterLayerWeight": 15
       },
       {
          "FilterAction": "FWP_ACTION_BLOCK",
          "FilterType": "APP",
          "FilterConditions": [
             {
                "DataValue": "C:\\Program Files\\Windows Defender\\MsMpEng.exe",
                "MatchType": "EQUAL",
                "DataType": "PATH"
             },
             {
                "DataValue": "C:\\Program Files\\Windows Defender\\NisSrv.exe",
                "MatchType": "EQUAL",
                "DataType": "PATH"
             },
             {
                "DataValue": "C:\\Program Files\\Windows Defender\\ConfigSecurityPolicy.exe",
                "MatchType": "EQUAL",
                "DataType": "PATH"
             },
             {
                "DataValue": "C:\\Program Files\\Windows Defender\\MpCmdRun.exe",
                "MatchType": "EQUAL",
                "DataType": "PATH"
             }

          ],
          "FilterKey": "A1F1A73B-E762-4A3E-B1EE-60BE052E754C",
          "FilterName": "WinDefender Filter",
          "FilterDesc": "WinDefender Filter - block outgoing ipv4",
          "FilterLayerName": "FWPM_LAYER_ALE_AUTH_CONNECT_V4",
          "FilterLayerWeight": 15
       }
    ]
  }
```
## Out of band data queries

`tools\js\index.html`


# Build 
```
git clone 
cd Shutter
msbuild libwfp\libwfp\libwfp.sln
msbuild Shutter.sln
```

# Dev

```
mkdir libwfp 
git submodule add https://github.com/mullvad/libwfp libwfp/libwfp
git submodule add https://github.com/mullvad/windows-libraries libwfp/windows-libraries
git submodule add https://github.com/nlohmann/json 
git submodule add https://github.com/jarro2783/cxxopts
```

## Ref
- Shuout out to @jamal0x42 for the cool name and the idea ;) 
