#!/usr/bin/env python3
"""Batch-diff the WinMain -> server-list function path against the
original binary (see tools/README.md's "Diffing a function against the
original") and render the results as a self-contained HTML report.

Usage:
    python3 tools/gen_diff_report.py [build/link_attempt] [report.html]

Requires the .obj files for the functions below to already exist (run
tools/msvc-env/_link_attempt.sh first) and an objdump whose path
contains "llvm-" (see diff_settings.py) - override with GB_OBJDUMP.
"""
import base64
import html
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIFF_PY = os.path.join(REPO, "tools", "asm-differ", "diff.py")
OBJDUMP = os.environ.get("GB_OBJDUMP", "llvm-objdump")

# (src file relative to repo root, original VA hex without 0x, decorated
# symbol hint - matched loosely so decoration mismatches still resolve)
FUNCS = [
    ("src/entry/WinMain.c", "40d8e0", "_WinMain@16"),
    ("src/entry/InitGame.c", "40eaa0", "_InitGame"),
    ("src/entry/ChangeGameState.c", "4122f0", "_ChangeGameState"),
    ("src/state_machine/State06_Logo2_OnEnter.c", "443280", "@State06_Logo2_OnEnter@4"),
    ("src/entry/GameTick.c", "413130", "_GameTick"),
    ("src/state_machine/State06_Logo2_OnTick.c", "443330", "@State06_Logo2_OnTick@4"),
    ("src/state_machine/State06_Logo2_OnExit.c", "4432c0", "@State06_Logo2_OnExit@4"),
    ("src/state_machine/State05_Logo1_OnEnter.c", "4433f0", "@State05_Logo1_OnEnter@4"),
    ("src/state_machine/State05_Logo1_OnExit.c", "443430", "@State05_Logo1_OnExit@4"),
    ("src/state_machine/State01_Title_OnEnter.c", "4e5370", "@State01_Title_OnEnter@4"),
    ("src/state_machine/State01_Title_OnTick.c", "4e5400", "@State01_Title_OnTick@4"),
    ("src/state_machine/State01_Title_OnExit.c", "4e53b0", "_State01_Title_OnExit"),
    ("src/state_machine/State02_ServerSelect_OnEnter.c", "4e14b0", "@State02_ServerSelect_OnEnter@4"),
    ("src/rendering/LoadSpriteSet.c", "4f1790", "_LoadSpriteSet"),
    ("src/ui_widget/AppendPersistentButtonName.c", "401740", "_AppendPersistentButtonName"),
    ("src/ui_widget/CreateButtonWidget.c", "406020", "_CreateButtonWidget"),
    ("src/ui_widget/BuildWorldListPanel.c", "5099d0", "_BuildWorldListPanel"),
    ("src/ui_widget/Panel_BaseConstructor.c", "505760", "_Panel_BaseConstructor"),
    ("src/ui_widget/CreateLabelWidget.c", "507ee0", "_CreateLabelWidget"),
    ("src/ui_widget/Widget_AddChild.c", "50e670", "_Widget_AddChild"),
    ("src/ui_widget/AtlArray_GrowBuffer.c", "50ed30", "_AtlArray_GrowBuffer"),
    ("src/ui_widget/Widget_MoveBy.c", "50e730", "_Widget_MoveBy"),
    ("src/ui_widget/CreateScrollListWidget.c", "5080a0", "_CreateScrollListWidget"),
    ("src/ui_widget/Widget_SetEnabled.c", "50e7d0", "_Widget_SetEnabled"),
    ("src/ui_widget/PanelManager_Register.c", "50eea0", "_PanelManager_Register"),
    ("src/ui_widget/PanelManager_PrependNode.c", "50f350", "_PanelManager_PrependNode"),
    ("src/network/BeginServerConnect.c", "4d2480", "_BeginServerConnect"),
    ("src/network/EncodeOutgoingPacketField.c", "40a380", "_EncodeOutgoingPacketField"),
    ("src/network/SignalConnectRequest.c", "4e5a50", "_SignalConnectRequest"),
    ("src/network/HandleSocketEvent.c", "4e57c0", "@HandleSocketEvent@8"),
    ("src/network/ConnectSocketToTarget.c", "4e59b0", "_ConnectSocketToTarget"),
    ("src/network/ReceiveFramedPackets.c", "4e5610", "_ReceiveFramedPackets"),
    ("src/network/CloseConnectionSocket.c", "4e5a20", "_CloseConnectionSocket"),
    ("src/network/ProcessIncomingPackets.c", "4d27e0", "_ProcessIncomingPackets"),
    ("src/network/DecodePacketBlocks.c", "4f7150", "_DecodePacketBlocks"),
    ("src/replay/WriteReplayEventRecord.c", "4104f0", "_WriteReplayEventRecord"),
    ("src/state_machine/State02_ServerSelect_ProcessPacket.c", "4e02b0", "@State02_ServerSelect_ProcessPacket@16"),
    ("src/rendering/RenderWrappedText.c", "41b4b0", "_RenderWrappedText"),
    ("src/network/PeekPacketChecksumBool.c", "4065a0", "_PeekPacketChecksumBool"),
    ("src/state_machine/ConnectToSelectedServer.c", "4e1bf0", "_ConnectToSelectedServer"),
    ("src/registry/InvokeWidget.c", "406300", "_InvokeWidget"),
]

SECTIONS = [
    ("Entry & state dispatch", [
        "src/entry/WinMain.c", "src/entry/InitGame.c", "src/entry/ChangeGameState.c",
        "src/entry/GameTick.c",
    ]),
    ("Logo2 (state 6)", [
        "src/state_machine/State06_Logo2_OnEnter.c",
        "src/state_machine/State06_Logo2_OnTick.c",
        "src/state_machine/State06_Logo2_OnExit.c",
    ]),
    ("Logo1 (state 5, alternate branch)", [
        "src/state_machine/State05_Logo1_OnEnter.c",
        "src/state_machine/State05_Logo1_OnExit.c",
    ]),
    ("Title (state 1)", [
        "src/state_machine/State01_Title_OnEnter.c",
        "src/state_machine/State01_Title_OnTick.c",
        "src/state_machine/State01_Title_OnExit.c",
    ]),
    ("ServerSelect (state 2) OnEnter + UI build", [
        "src/state_machine/State02_ServerSelect_OnEnter.c",
        "src/rendering/LoadSpriteSet.c",
        "src/ui_widget/AppendPersistentButtonName.c",
        "src/ui_widget/CreateButtonWidget.c",
        "src/ui_widget/BuildWorldListPanel.c",
        "src/ui_widget/Panel_BaseConstructor.c",
        "src/ui_widget/CreateLabelWidget.c",
        "src/ui_widget/Widget_AddChild.c",
        "src/ui_widget/AtlArray_GrowBuffer.c",
        "src/ui_widget/Widget_MoveBy.c",
        "src/ui_widget/CreateScrollListWidget.c",
        "src/ui_widget/Widget_SetEnabled.c",
        "src/ui_widget/PanelManager_Register.c",
        "src/ui_widget/PanelManager_PrependNode.c",
    ]),
    ("Broker connect", [
        "src/network/BeginServerConnect.c",
        "src/network/EncodeOutgoingPacketField.c",
        "src/network/SignalConnectRequest.c",
    ]),
    ("Socket-event pump (worker thread)", [
        "src/network/HandleSocketEvent.c",
        "src/network/ConnectSocketToTarget.c",
        "src/network/ReceiveFramedPackets.c",
        "src/network/CloseConnectionSocket.c",
    ]),
    ("Per-tick packet drain", [
        "src/network/ProcessIncomingPackets.c",
        "src/network/DecodePacketBlocks.c",
        "src/replay/WriteReplayEventRecord.c",
    ]),
    ("ServerSelect ProcessPacket (list population)", [
        "src/state_machine/State02_ServerSelect_ProcessPacket.c",
        "src/rendering/RenderWrappedText.c",
        "src/network/PeekPacketChecksumBool.c",
        "src/state_machine/ConnectToSelectedServer.c",
        "src/registry/InvokeWidget.c",
    ]),
]


def obj_path_for(build_dir, src_rel):
    # Mirrors _link_attempt.sh's own naming: tr '/' '_', then
    # sed 's/\.cpp$/.obj/;s/\.c$/.obj/' - .cpp must be checked before .c
    # since both share the trailing "c".
    obj_name = src_rel.replace("/", "_")
    if obj_name.endswith(".cpp"):
        obj_name = obj_name[:-4] + ".obj"
    elif obj_name.endswith(".c"):
        obj_name = obj_name[:-2] + ".obj"
    else:
        obj_name = obj_name + ".obj"
    return os.path.join(build_dir, obj_name)


def find_symbol_and_size(objfile, hint):
    """Return (symbol_name, size_bytes) by scanning objdump -d output."""
    try:
        out = subprocess.run(
            [OBJDUMP, "-d", objfile], capture_output=True, text=True, timeout=30
        ).stdout
    except Exception:
        return None, None
    lines = out.splitlines()
    starts = []
    for i, line in enumerate(lines):
        line = line.strip()
        if line.endswith(">:") and " <" in line:
            addr_str, rest = line.split(" <", 1)
            name = rest.rstrip(">:")
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            starts.append((addr, name, i))
    if not starts:
        return None, None
    hint_bare = hint.lstrip("_@").split("@")[0].lower()
    match = None
    for addr, name, idx in starts:
        bare = name.lstrip("_@").split("@")[0].lower()
        if bare == hint_bare:
            match = (addr, name, idx)
            break
    if match is None:
        return None, None
    addr, name, idx = match
    # size: bytes until the next REAL (non-label, non-jumptable) symbol
    # start, since MSVC emits internal $L<n>/switch-table labels inside
    # the same function that shouldn't be treated as a boundary.
    next_addr = None
    for a2, n2, i2 in starts:
        if a2 > addr and not n2.startswith("$") and "switchD" not in n2 and "caseD" not in n2:
            next_addr = a2
            break
    if next_addr is not None:
        size = next_addr - addr
    else:
        last_off = addr
        for line in lines[idx:]:
            line = line.strip()
            if not line or line.endswith(":"):
                continue
            parts = line.split(":", 1)
            if len(parts) != 2:
                continue
            try:
                off = int(parts[0].strip(), 16)
            except ValueError:
                continue
            last_off = off
        size = max(last_off - addr + 16, 4)
    return name, size


def run_diff(build_dir, src_rel, va_hex, hint, size_override=None):
    """size_override bypasses find_symbol_and_size's "next symbol at a
    higher address" heuristic, which breaks when a single object has many
    COMDAT-per-function sections that each start at 0x0 (MSVC 7.1's normal
    layout for C++ member functions) - every function in that object then
    looks like it starts at the same address, so the heuristic can't tell
    them apart by position. Still uses find_symbol_and_size for the actual
    symbol-name lookup (that part doesn't depend on addressing)."""
    objfile = obj_path_for(build_dir, src_rel)
    if not os.path.isfile(objfile):
        return {"file": src_rel, "status": "NO_OBJ", "obj": objfile}
    sym, size = find_symbol_and_size(objfile, hint)
    if sym is None:
        return {"file": src_rel, "status": "NO_SYM", "obj": objfile, "hint": hint}
    if size_override is not None:
        size = size_override
    start = int(va_hex, 16)
    end = start + max(size, 4)
    env = dict(os.environ)
    env["GB_MYIMG"] = objfile
    env["GB_OBJDUMP"] = OBJDUMP

    def _run(fmt):
        return subprocess.run(
            ["python3", DIFF_PY, "-e", sym, hex(start), hex(end), "--format", fmt, "--no-pager"],
            cwd=REPO, capture_output=True, text=True, timeout=60, env=env,
        )

    try:
        proc = _run("json")
    except Exception as e:
        return {"file": src_rel, "status": "DIFF_ERROR", "error": str(e)}
    if proc.returncode != 0:
        return {"file": src_rel, "status": "DIFF_FAIL", "stderr": proc.stderr[-500:]}
    try:
        data = json.loads(proc.stdout)
    except Exception:
        return {"file": src_rel, "status": "BAD_JSON", "stdout": proc.stdout[:300]}

    cur = data.get("current_score") if isinstance(data, dict) else None
    mx = data.get("max_score") if isinstance(data, dict) else None
    pct = None
    if isinstance(cur, (int, float)) and isinstance(mx, (int, float)) and mx > 0:
        pct = round(100.0 * max(0.0, (mx - cur)) / mx, 1)

    plain = ""
    try:
        plain = _run("plain").stdout
    except Exception:
        pass

    return {
        "file": src_rel, "status": "OK", "symbol": sym, "size": size,
        "current_score": cur, "max_score": mx, "match_pct": pct, "plain": plain,
    }


def score_class(pct):
    if pct is None:
        return "na"
    if pct >= 60:
        return "good"
    if pct >= 25:
        return "mid"
    return "poor"


def render_diff_line(line):
    esc = html.escape(line)
    cls = "diffline"
    if re.search(r"\s\|\s", line):
        cls += " d-neq"
    elif re.search(r"\si\s", line):
        cls += " d-imm"
    elif re.search(r"\sr\s", line):
        cls += " d-reloc"
    elif "IMAGE_REL" in line:
        cls += " d-relocref"
    elif re.match(r"^\s*$", line):
        cls += " d-blank"
    return f'<span class="{cls}">{esc}</span>'


def render_plain(plain):
    return "\n".join(render_diff_line(l) for l in plain.splitlines())


def find_font():
    candidates = [
        "/usr/share/fonts/truetype/noto/NotoSansMono-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
    ]
    for c in candidates:
        if os.path.isfile(c):
            return c
    return None


def render_report(results, out_path, sections=None, report_title=None, report_sub=None,
                   obj_dir_label="build/link_attempt/"):
    sections = SECTIONS if sections is None else sections
    report_title = report_title or "WinMain → Server List: disassembly diff"
    report_sub = report_sub or (
        "Instruction-level comparison of every function on the startup path "
        "(original <code>GunBound.gme</code> vs. the current MSVC 7.10 recompile), "
        "scored with <code>tools/asm-differ</code>. Low scores are largely expected: "
        "unresolved relocations in an unlinked <code>.obj</code> inflate the diff, and "
        "MSVC's own register allocation rarely reproduces byte-for-byte, even for "
        "logically correct code &mdash; click a row to inspect."
    )
    by_file = {r["file"]: r for r in results}
    sections_html = []
    idx = 0
    seen = set()
    for title, files in sections:
        rows = []
        for f in files:
            r = by_file.get(f)
            seen.add(f)
            idx += 1
            rid = f"fn{idx}"
            if not r or r.get("status") != "OK":
                rows.append(f"""
                <tr class="row na" data-target="{rid}">
                  <td class="fn"><code>{html.escape(f)}</code></td>
                  <td class="sym">&mdash;</td>
                  <td class="pct na">n/a</td>
                  <td class="bar"><div class="bartrack"></div></td>
                  <td class="size">&mdash;</td>
                </tr>""")
                continue
            pct = r.get("match_pct") or 0.0
            cls = score_class(pct)
            rows.append(f"""
            <tr class="row {cls}" data-target="{rid}" tabindex="0">
              <td class="fn"><code>{html.escape(f)}</code></td>
              <td class="sym"><code>{html.escape(r.get('symbol',''))}</code></td>
              <td class="pct {cls}">{pct:.1f}%</td>
              <td class="bar"><div class="bartrack"><div class="barfill {cls}" style="width:{pct:.1f}%"></div></div></td>
              <td class="size">{r.get('size','')}&nbsp;B</td>
            </tr>
            <tr class="detail" id="{rid}"><td colspan="5"><div class="diffwrap"><pre>{render_plain(r.get('plain',''))}</pre></div></td></tr>""")
        sections_html.append((title, "".join(rows)))

    leftover = [f for f in by_file if f not in seen]
    if leftover:
        rows = []
        for f in leftover:
            r = by_file[f]
            idx += 1
            rid = f"fn{idx}"
            pct = r.get("match_pct") or 0.0
            cls = score_class(pct)
            rows.append(f"""
            <tr class="row {cls}" data-target="{rid}" tabindex="0">
              <td class="fn"><code>{html.escape(f)}</code></td>
              <td class="sym"><code>{html.escape(r.get('symbol',''))}</code></td>
              <td class="pct {cls}">{pct:.1f}%</td>
              <td class="bar"><div class="bartrack"><div class="barfill {cls}" style="width:{pct:.1f}%"></div></div></td>
              <td class="size">{r.get('size','')}&nbsp;B</td>
            </tr>
            <tr class="detail" id="{rid}"><td colspan="5"><div class="diffwrap"><pre>{render_plain(r.get('plain',''))}</pre></div></td></tr>""")
        sections_html.append(("Other", "".join(rows)))

    all_pcts = [r.get("match_pct") or 0.0 for r in results if r.get("status") == "OK"]
    avg_pct = sum(all_pcts) / len(all_pcts) if all_pcts else 0.0
    n_good = sum(1 for p in all_pcts if p >= 60)
    n_mid = sum(1 for p in all_pcts if 25 <= p < 60)
    n_poor = sum(1 for p in all_pcts if p < 25)

    sections_markup = ""
    for title, rows in sections_html:
        sections_markup += f"""
    <section class="group">
      <h2>{html.escape(title)}</h2>
      <table>
        <thead><tr><th>File</th><th>Symbol</th><th>Match</th><th></th><th>Size</th></tr></thead>
        <tbody>{rows}</tbody>
      </table>
    </section>"""

    font_path = find_font()
    font_face = ""
    if font_path:
        with open(font_path, "rb") as f:
            font_b64 = base64.b64encode(f.read()).decode("ascii")
        font_face = f"""@font-face {{
  font-family: 'JBMono';
  src: url(data:font/truetype;base64,{font_b64}) format('truetype');
  font-weight: 400 700;
  font-display: swap;
}}"""

    page = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>{html.escape(report_title)}</title>
<style>
{font_face}
:root {{
  --bg: #0d1117; --panel: #12161d; --panel2: #161b22; --border: #232a35;
  --text: #c9d1d9; --text-dim: #7d8794; --accent: #58a6ff;
  --good: #3fb950; --mid: #d29922; --poor: #f85149;
  --mono: 'JBMono', ui-monospace, 'SF Mono', Consolas, monospace;
  --sans: -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
}}
@media (prefers-color-scheme: light) {{
  :root {{
    --bg: #f6f8fa; --panel: #ffffff; --panel2: #f0f2f5; --border: #d0d7de;
    --text: #1f2328; --text-dim: #59636e; --accent: #0969da;
    --good: #1a7f37; --mid: #9a6700; --poor: #cf222e;
  }}
}}
:root[data-theme="dark"] {{
  --bg: #0d1117; --panel: #12161d; --panel2: #161b22; --border: #232a35;
  --text: #c9d1d9; --text-dim: #7d8794; --accent: #58a6ff;
  --good: #3fb950; --mid: #d29922; --poor: #f85149;
}}
:root[data-theme="light"] {{
  --bg: #f6f8fa; --panel: #ffffff; --panel2: #f0f2f5; --border: #d0d7de;
  --text: #1f2328; --text-dim: #59636e; --accent: #0969da;
  --good: #1a7f37; --mid: #9a6700; --poor: #cf222e;
}}
* {{ box-sizing: border-box; }}
body {{ margin: 0; background: var(--bg); color: var(--text); font-family: var(--sans); line-height: 1.5; -webkit-font-smoothing: antialiased; }}
header {{ padding: 2.5rem clamp(1rem, 4vw, 3rem) 1.5rem; border-bottom: 1px solid var(--border); }}
header h1 {{ font-family: var(--mono); font-size: clamp(1.3rem, 2.4vw, 1.7rem); margin: 0 0 0.4rem; font-weight: 600; text-wrap: balance; letter-spacing: -0.01em; }}
header p.sub {{ margin: 0; color: var(--text-dim); font-size: 0.92rem; max-width: 65ch; }}
.stats {{ display: flex; gap: 1.5rem; margin-top: 1.4rem; flex-wrap: wrap; }}
.stat {{ background: var(--panel2); border: 1px solid var(--border); border-radius: 6px; padding: 0.7rem 1rem; min-width: 7rem; }}
.stat .n {{ font-family: var(--mono); font-size: 1.4rem; font-weight: 600; font-variant-numeric: tabular-nums; }}
.stat .l {{ font-size: 0.72rem; color: var(--text-dim); text-transform: uppercase; letter-spacing: 0.04em; margin-top: 0.15rem; }}
.stat.good .n {{ color: var(--good); }} .stat.mid .n {{ color: var(--mid); }} .stat.poor .n {{ color: var(--poor); }}
main {{ padding: 1.5rem clamp(1rem, 4vw, 3rem) 4rem; max-width: 1400px; margin: 0 auto; }}
.legend {{ display: flex; gap: 1.2rem; flex-wrap: wrap; margin-bottom: 1.6rem; font-size: 0.8rem; color: var(--text-dim); }}
.dot {{ display:inline-block; width:0.6rem; height:0.6rem; border-radius:50%; margin-right:0.35rem; }}
.dot.good {{ background: var(--good); }} .dot.mid {{ background: var(--mid); }} .dot.poor {{ background: var(--poor); }}
section.group {{ margin-bottom: 2.2rem; }}
section.group h2 {{ font-size: 0.95rem; text-transform: uppercase; letter-spacing: 0.05em; color: var(--text-dim); font-weight: 600; margin: 0 0 0.6rem; border-bottom: 1px solid var(--border); padding-bottom: 0.5rem; }}
table {{ width: 100%; border-collapse: collapse; font-size: 0.87rem; }}
thead th {{ text-align: left; font-size: 0.7rem; text-transform: uppercase; letter-spacing: 0.04em; color: var(--text-dim); padding: 0.35rem 0.6rem; font-weight: 600; }}
tr.row td {{ padding: 0.5rem 0.6rem; border-top: 1px solid var(--border); vertical-align: middle; cursor: pointer; }}
tr.row:hover td {{ background: var(--panel2); }}
tr.row.expanded td {{ background: var(--panel2); }}
td.fn code {{ font-family: var(--mono); font-size: 0.83rem; }}
td.sym code {{ font-family: var(--mono); font-size: 0.78rem; color: var(--text-dim); }}
td.pct {{ font-family: var(--mono); font-variant-numeric: tabular-nums; font-weight: 600; width: 4.5rem; }}
td.pct.good {{ color: var(--good); }} td.pct.mid {{ color: var(--mid); }} td.pct.poor {{ color: var(--poor); }} td.pct.na {{ color: var(--text-dim); font-weight:400; }}
td.bar {{ width: 12rem; }}
.bartrack {{ background: var(--border); border-radius: 3px; height: 6px; overflow: hidden; }}
.barfill {{ height: 100%; border-radius: 3px; }}
.barfill.good {{ background: var(--good); }} .barfill.mid {{ background: var(--mid); }} .barfill.poor {{ background: var(--poor); }}
td.size {{ font-family: var(--mono); font-size: 0.78rem; color: var(--text-dim); text-align: right; font-variant-numeric: tabular-nums; }}
tr.detail {{ display: none; }}
tr.detail.open {{ display: table-row; }}
tr.detail td {{ padding: 0; border-top: none; }}
.diffwrap {{ background: var(--panel); border: 1px solid var(--border); border-top: none; overflow-x: auto; max-height: 70vh; overflow-y: auto; }}
.diffwrap pre {{ margin: 0; padding: 0.9rem 1rem; font-family: var(--mono); font-size: 0.75rem; line-height: 1.45; white-space: pre; }}
.diffline {{ display: block; }}
.d-neq {{ color: var(--poor); }} .d-imm {{ color: var(--mid); }} .d-reloc {{ color: var(--accent); }}
.d-relocref {{ color: var(--text-dim); font-style: italic; }} .d-blank {{ display: none; }}
footer {{ padding: 1.5rem clamp(1rem, 4vw, 3rem) 3rem; color: var(--text-dim); font-size: 0.8rem; border-top: 1px solid var(--border); }}
footer code {{ font-family: var(--mono); }}
</style>
</head>
<body>
<header>
  <h1>{html.escape(report_title)}</h1>
  <p class="sub">{report_sub}</p>
  <div class="stats">
    <div class="stat"><div class="n">{len(all_pcts)}</div><div class="l">Functions</div></div>
    <div class="stat"><div class="n">{avg_pct:.1f}%</div><div class="l">Avg match</div></div>
    <div class="stat good"><div class="n">{n_good}</div><div class="l">&ge;60%</div></div>
    <div class="stat mid"><div class="n">{n_mid}</div><div class="l">25&ndash;60%</div></div>
    <div class="stat poor"><div class="n">{n_poor}</div><div class="l">&lt;25%</div></div>
  </div>
</header>
<main>
  <div class="legend">
    <span><span class="dot good"></span>&ge; 60% instruction match</span>
    <span><span class="dot mid"></span>25&ndash;60%</span>
    <span><span class="dot poor"></span>&lt; 25% (register alloc noise, unresolved relocs, or a real gap)</span>
  </div>
  {sections_markup}
</main>
<footer>
  Generated by <code>tools/gen_diff_report.py</code> (asm-differ <code>-e</code> ELF-symbol mode) against objects from <code>{html.escape(obj_dir_label)}</code>.
</footer>
<script>
document.querySelectorAll('tr.row').forEach(function(row) {{
  row.addEventListener('click', function() {{
    var id = row.getAttribute('data-target');
    var detail = document.getElementById(id);
    if (!detail) return;
    var open = detail.classList.toggle('open');
    row.classList.toggle('expanded', open);
  }});
  row.addEventListener('keydown', function(e) {{
    if (e.key === 'Enter' || e.key === ' ') {{ e.preventDefault(); row.click(); }}
  }});
}});
</script>
</body>
</html>
"""
    with open(out_path, "w") as f:
        f.write(page)
    return len(page)


def main():
    build_dir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(REPO, "build", "link_attempt")
    out_path = sys.argv[2] if len(sys.argv) > 2 else os.path.join(REPO, "diff-report.html")

    results = []
    for src_rel, va_hex, hint in FUNCS:
        r = run_diff(build_dir, src_rel, va_hex, hint)
        print(f"{src_rel}: {r.get('status')} {r.get('symbol', '')} {r.get('size', '')}", file=sys.stderr)
        results.append(r)

    json_path = os.path.splitext(out_path)[0] + ".json"
    with open(json_path, "w") as f:
        json.dump(results, f, indent=2)

    size = render_report(results, out_path)
    print(f"wrote {out_path} ({size} bytes) and {json_path}", file=sys.stderr)


if __name__ == "__main__":
    main()
