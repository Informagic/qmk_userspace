#ifndef NEO2CHARS_H
#define NEO2CHARS_H

enum unicode_names {
  NEO2_L1_AND_2_AE_LOWERCASE,
  NEO2_L1_AND_2_AE_UPPERCASE,
  NEO2_L1_AND_2_OE_LOWERCASE,
  NEO2_L1_AND_2_OE_UPPERCASE,
  NEO2_L1_AND_2_UE_LOWERCASE,
  NEO2_L1_AND_2_UE_UPPERCASE,
  NEO2_L1_AND_2_SS_LOWERCASE,
  NEO2_L1_AND_2_SS_UPPERCASE,
  NEO2_L1_AND_2_BULLET,
  NEO2_L1_AND_2_DEGREE,
  NEO2_L1_AND_2_SECTION,
  NEO2_L1_AND_2_ANGLEQUOTE_RIGHT,
  NEO2_L1_AND_2_ANGLEQUOTE_LEFT,
  NEO2_L1_AND_2_EURO,
  NEO2_L1_AND_2_DOUBLEQUOTE_LOW,
  NEO2_L1_AND_2_DOUBLEQUOTE_LEFT,
  NEO2_L1_AND_2_DOUBLEQUOTE_RIGHT,
  NEO2_L1_AND_2_DASH_EN,
  NEO2_L1_AND_2_DASH_EM,
  NEO2_L1_AND_2_DEAD_ACUTE,
  NEO2_L1_AND_2_DEAD_GRAVE,
  NEO2_L1_AND_2_DEAD_CIRCUMFLEX,
  NEO2_L1_AND_2_DEAD_CEDILLA,
  NEO2_L1_AND_2_DEAD_TILDE,
  NEO2_L1_AND_2_DEAD_CARON,

  NEO2_L3_ELLIPSIS
};



#define NEO2_SS                 UP(NEO2_L1_AND_2_SS_LOWERCASE, NEO2_L1_AND_2_SS_UPPERCASE)
#define NEO2_AE                 UP(NEO2_L1_AND_2_AE_LOWERCASE, NEO2_L1_AND_2_AE_UPPERCASE)
#define NEO2_OE                 UP(NEO2_L1_AND_2_OE_LOWERCASE, NEO2_L1_AND_2_OE_UPPERCASE)
#define NEO2_UE                 UP(NEO2_L1_AND_2_UE_LOWERCASE, NEO2_L1_AND_2_UE_UPPERCASE)
#define NEO2_ACUTE_CEDILLA      UP(NEO2_L1_AND_2_DEAD_ACUTE, NEO2_L1_AND_2_DEAD_CEDILLA)
#define NEO2_GRAVE_TILDE        UP(NEO2_L1_AND_2_DEAD_GRAVE, NEO2_L1_AND_2_DEAD_TILDE)
#define NEO2_CIRCUMFLEX_CARON   UP(NEO2_L1_AND_2_DEAD_CIRCUMFLEX, NEO2_L1_AND_2_DEAD_CARON)

#define NEO2_L3_ELLIPSIS             UC(0x2026)

#define NEO2_L4_FEMININE_ORDINAL     UC(0x00AA)                  // ª
#define NEO2_L4_MASCULINE_ORDINAL    UC(0x00BA)                  // º
#define NEO2_L4_NUMERO_SIGN          KC_NO                       // №
#define NEO2_L4_MIDDLE_DOT           UC(0x00B7)                  // ·
#define NEO2_L4_BRITISH_POUND        UC(0x00A3)                  // £
#define NEO2_L4_CURRENCY_SIGN        UC(0x00A4)                  // ¤
#define NEO2_L4_INV_EXCLAMATION      UC(0x00A1)                  // ¡
#define NEO2_L4_INV_QUESTIONMARK     UC(0x00BF)                  // ¿

#if(0)
// NEO_1_AND_2 special characters
#define NEO2_L1_AE

// NEO_3 special characters
#define NEO2_L3_CAPITAL_SS           RSA(DE_S)                   // ẞ
#define NEO2_L3_CAPITAL_UE           S(DE_UDIA)                  // Ü
#define NEO2_L3_CAPITAL_OE           S(DE_ODIA)                  // Ö
#define NEO2_L3_CAPITAL_AE           S(DE_ADIA)                  // Ä
#define NEO2_L3_SUPERSCRIPT_1        RALT(DE_1)                  // ¹
#define NEO2_L3_SUPERSCRIPT_2        DE_SUP2                     // ²
#define NEO2_L3_SUPERSCRIPT_3        DE_SUP3                     // ³
#define NEO2_L3_RSAQUO               RSA(DE_Y)                   // ›
#define NEO2_L3_LSAQUO               RSA(DE_X)                   // ‹
#define NEO2_L3_RAQUO                RALT(DE_Y)                  // »
#define NEO2_L3_LAQUO                RALT(DE_X)                  // «
#define NEO2_L3_CENT                 RALT(DE_C)                  // ¢
#define NEO2_L3_YEN                  RSA(DE_Z)                   // ¥
#define NEO2_L3_SBQUO                RSA(DE_V)                   // ‚
#define NEO2_L3_LEFT_SINGLE_QUOTE    RSA(DE_B)                   // ‘
#define NEO2_L3_RIGHT_SINGLE_QUOTE   RSA(DE_N)                   // ’
#define NEO2_L3_LOW9_DBQUOTE         RALT(DE_V)                  // „
#define NEO2_L3_LEFT_DBQUOTE         RALT(DE_B)                  // “
#define NEO2_L3_RIGHT_DBQUOTE        RALT(DE_N)                  // ”
#define NEO2_L3_ELLIPSIS             RALT(DE_DOT)                // …
#define NEO2_L3_UNDERSCORE           DE_UNDS                     // _
#define NEO2_L3_LBRACKET             DE_LBRC                     // [
#define NEO2_L3_RBRACKET             DE_RBRC                     // ]
#define NEO2_L3_CIRCUMFLEX           DE_CIRC                     // ^
#define NEO2_L3_EXCLAMATION          DE_EXLM                     // !
#define NEO2_L3_LESSTHAN             DE_LABK                     // <
#define NEO2_L3_GREATERTHAN          DE_RABK                     // >
#define NEO2_L3_EQUAL                DE_EQL                      // =
#define NEO2_L3_AMPERSAND            DE_AMPR                     // &
#define NEO2_L3_SMALL_LONG_S         RALT(DE_S)                  // ſ
#define NEO2_L3_BSLASH               DE_BSLS                     // (backslash)
#define NEO2_L3_SLASH                DE_SLSH                     // /
#define NEO2_L3_CLBRACKET            DE_LCBR                     // {
#define NEO2_L3_CRBRACKET            DE_RCBR                     // }
#define NEO2_L3_ASTERISK             DE_ASTR                     // *
#define NEO2_L3_QUESTIONMARK         DE_QUES                     // ?
#define NEO2_L3_LPARENTHESES         DE_LPRN                     // (
#define NEO2_L3_RPARENTHESES         DE_RPRN                     // )
#define NEO2_L3_HYPHEN_MINUS         DE_MINS                     // -
#define NEO2_L3_COLON                DE_COLN                     // :
#define NEO2_L3_AT                   DE_AT                       // @
#define NEO2_L3_HASH                 DE_HASH                     // #
#define NEO2_L3_PIPE                 DE_PIPE                     // |
#define NEO2_L3_TILDE                DE_TILD                     // ~
#define NEO2_L3_BACKTICK             DE_GRV                      // `
#define NEO2_L3_PLUS                 DE_PLUS                     // +
#define NEO2_L3_PERCENT              DE_PERC                     // %
#define NEO2_L3_DOUBLE_QUOTE         DE_DQUO                     // "
#define NEO2_L3_SINGLE_QUOTE         DE_QUOT                     // '
#define NEO2_L3_SEMICOLON            DE_SCLN                     // ;

// NEO_4 special characters
#define NEO2_L3_FEMININE_ORDINAL     RSA(DE_F)                   // ª
#define NEO2_L3_MASCULINE_ORDINAL    RSA(DE_M)                   // º
#define NEO2_L3_NUMERO_SIGN          KC_NO                       // №
#define NEO2_L3_MIDDLE_DOT           RALT(DE_COMM)               // ·
#define NEO2_L3_BRITISH_POUND        RSA(DE_3)                   // £
#define NEO2_L3_CURRENCY_SIGN        RSA(DE_4)                   // ¤
#define NEO2_L3_INV_EXCLAMATION      RSA(DE_1)                   // ¡
#define NEO2_L3_INV_QUESTIONMARK     RSA(DE_SS)                  // ¿
#define NEO2_L3_DOLLAR               DE_DLR                      // $
#define NEO2_L3_EN_DASH              RALT(DE_MINS)               // –
#define NEO2_L3_EM_DASH              RSA(DE_MINS)                // —
#endif
#endif
