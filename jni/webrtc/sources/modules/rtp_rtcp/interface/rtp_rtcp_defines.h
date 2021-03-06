/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MODULES_RTP_RTCP_INTERFACE_RTP_RTCP_DEFINES_H_
#define WEBRTC_MODULES_RTP_RTCP_INTERFACE_RTP_RTCP_DEFINES_H_

#include "typedefs.h"
#include "module_common_types.h"

#ifndef NULL
    #define NULL    0
#endif

#define RTCP_CNAME_SIZE 256    // RFC 3550 page 44, including null termination
#define IP_PACKET_SIZE 1500    // we assume ethernet
#define MAX_NUMBER_OF_PARALLEL_TELEPHONE_EVENTS 10
#define TIMEOUT_SEI_MESSAGES_MS 30000   // in milliseconds

namespace webrtc{
enum RTCPMethod
{
    kRtcpOff          = 0,
    kRtcpCompound     = 1,
    kRtcpNonCompound = 2
};

enum RTPAliveType
{
    kRtpDead   = 0,
    kRtpNoRtp = 1,
    kRtpAlive  = 2
};

enum StorageType {
  kDontStore,
  kDontRetransmit,
  kAllowRetransmission
};

enum RTPExtensionType
{
   kRtpExtensionNone,
   kRtpExtensionTransmissionTimeOffset,
   kRtpExtensionAudioLevel,
};

enum RTCPAppSubTypes
{
    kAppSubtypeBwe     = 0x00
};

enum RTCPPacketType
{
    kRtcpReport         = 0x0001,
    kRtcpSr             = 0x0002,
    kRtcpRr             = 0x0004,
    kRtcpBye            = 0x0008,
    kRtcpPli            = 0x0010,
    kRtcpNack           = 0x0020,
    kRtcpFir            = 0x0040,
    kRtcpTmmbr          = 0x0080,
    kRtcpTmmbn          = 0x0100,
    kRtcpSrReq          = 0x0200,
    kRtcpXrVoipMetric   = 0x0400,
    kRtcpApp            = 0x0800,
    kRtcpSli            = 0x4000,
    kRtcpRpsi           = 0x8000,
    kRtcpRemb           = 0x10000,
    kRtcpTransmissionTimeOffset = 0x20000
};

enum KeyFrameRequestMethod
{
    kKeyFrameReqFirRtp    = 1,
    kKeyFrameReqPliRtcp   = 2,
    kKeyFrameReqFirRtcp   = 3
};

enum RtpRtcpPacketType
{
    kPacketRtp        = 0,
    kPacketKeepAlive = 1
};

enum NACKMethod
{
    kNackOff      = 0,
    kNackRtcp     = 2
};

enum RetransmissionMode {
  kRetransmitOff          = 0x0,
  kRetransmitFECPackets   = 0x1,
  kRetransmitBaseLayer    = 0x2,
  kRetransmitHigherLayers = 0x4,
  kRetransmitAllPackets   = 0xFF
};

struct RTCPSenderInfo
{
    WebRtc_UWord32 NTPseconds;
    WebRtc_UWord32 NTPfraction;
    WebRtc_UWord32 RTPtimeStamp;
    WebRtc_UWord32 sendPacketCount;
    WebRtc_UWord32 sendOctetCount;
};

struct RTCPReportBlock
{
  // Fields as described by RFC 3550 6.4.2.
    WebRtc_UWord32 remoteSSRC;  // SSRC of sender of this report.
    WebRtc_UWord32 sourceSSRC;  // SSRC of the RTP packet sender.
    WebRtc_UWord8 fractionLost;
    WebRtc_UWord32 cumulativeLost;  // 24 bits valid
    WebRtc_UWord32 extendedHighSeqNum;
    WebRtc_UWord32 jitter;
    WebRtc_UWord32 lastSR;
    WebRtc_UWord32 delaySinceLastSR;
};

class RtpData
{
public:
    virtual WebRtc_Word32 OnReceivedPayloadData(
        const WebRtc_UWord8* payloadData,
        const WebRtc_UWord16 payloadSize,
        const WebRtcRTPHeader* rtpHeader) = 0;
protected:
    virtual ~RtpData() {}
};

class RtcpFeedback
{
public:
    virtual void OnApplicationDataReceived(const WebRtc_Word32 /*id*/,
                                           const WebRtc_UWord8 /*subType*/,
                                           const WebRtc_UWord32 /*name*/,
                                           const WebRtc_UWord16 /*length*/,
                                           const WebRtc_UWord8* /*data*/)  {};

    virtual void OnXRVoIPMetricReceived(
        const WebRtc_Word32 /*id*/,
        const RTCPVoIPMetric* /*metric*/)  {};

    virtual void OnRTCPPacketTimeout(const WebRtc_Word32 /*id*/)  {};

    // |ntp_secs|, |ntp_frac| and |timestamp| are the NTP time and RTP timestamp
    // parsed from the RTCP sender report from the sender with ssrc
    // |senderSSRC|.
    virtual void OnSendReportReceived(const WebRtc_Word32 id,
                                      const WebRtc_UWord32 senderSSRC,
                                      uint32_t ntp_secs,
                                      uint32_t ntp_frac,
                                      uint32_t timestamp)  {};

    virtual void OnReceiveReportReceived(const WebRtc_Word32 id,
                                         const WebRtc_UWord32 senderSSRC)  {};

protected:
    virtual ~RtcpFeedback() {}
};

class RtpFeedback
{
public:
    // Receiving payload change or SSRC change. (return success!)
    /*
    *   channels    - number of channels in codec (1 = mono, 2 = stereo)
    */
    virtual WebRtc_Word32 OnInitializeDecoder(
        const WebRtc_Word32 id,
        const WebRtc_Word8 payloadType,
        const char payloadName[RTP_PAYLOAD_NAME_SIZE],
        const int frequency,
        const WebRtc_UWord8 channels,
        const WebRtc_UWord32 rate) = 0;

    virtual void OnPacketTimeout(const WebRtc_Word32 id) = 0;

    virtual void OnReceivedPacket(const WebRtc_Word32 id,
                                  const RtpRtcpPacketType packetType) = 0;

    virtual void OnPeriodicDeadOrAlive(const WebRtc_Word32 id,
                                       const RTPAliveType alive) = 0;

    virtual void OnIncomingSSRCChanged( const WebRtc_Word32 id,
                                        const WebRtc_UWord32 SSRC) = 0;

    virtual void OnIncomingCSRCChanged( const WebRtc_Word32 id,
                                        const WebRtc_UWord32 CSRC,
                                        const bool added) = 0;

protected:
    virtual ~RtpFeedback() {}
};

class RtpAudioFeedback {
 public:
  virtual void OnReceivedTelephoneEvent(const WebRtc_Word32 id,
                                        const WebRtc_UWord8 event,
                                        const bool endOfEvent) = 0;

  virtual void OnPlayTelephoneEvent(const WebRtc_Word32 id,
                                    const WebRtc_UWord8 event,
                                    const WebRtc_UWord16 lengthMs,
                                    const WebRtc_UWord8 volume) = 0;
 protected:
  virtual ~RtpAudioFeedback() {}
};

class RtcpIntraFrameObserver {
 public:
  virtual void OnReceivedIntraFrameRequest(uint32_t ssrc) = 0;

  virtual void OnReceivedSLI(uint32_t ssrc,
                             uint8_t picture_id) = 0;

  virtual void OnReceivedRPSI(uint32_t ssrc,
                              uint64_t picture_id) = 0;

  virtual void OnLocalSsrcChanged(uint32_t old_ssrc, uint32_t new_ssrc) = 0;

  virtual ~RtcpIntraFrameObserver() {}
};

class RtcpBandwidthObserver {
 public:
  // REMB or TMMBR
  virtual void OnReceivedEstimatedBitrate(const uint32_t bitrate) = 0;

  virtual void OnReceivedRtcpReceiverReport(
      const uint32_t ssrc,
      const uint8_t fraction_loss,
      const uint32_t rtt,
      const uint32_t last_received_extended_high_seqNum,
      const uint32_t now_ms) = 0;

  virtual ~RtcpBandwidthObserver() {}
};

// A clock interface that allows reading of absolute and relative
// timestamps in an RTP/RTCP module.
class RtpRtcpClock {
 public:
  virtual ~RtpRtcpClock() {}

  // Return a timestamp in milliseconds relative to some arbitrary
  // source; the source is fixed for this clock.
  virtual WebRtc_Word64 GetTimeInMS() = 0;

  // Retrieve an NTP absolute timestamp.
  virtual void CurrentNTP(WebRtc_UWord32& secs, WebRtc_UWord32& frac) = 0;
};

} // namespace webrtc
#endif // WEBRTC_MODULES_RTP_RTCP_INTERFACE_RTP_RTCP_DEFINES_H_
