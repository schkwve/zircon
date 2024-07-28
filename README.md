# Zircon

A small, yet powerful IRC client

<details open="open">
<summary>Table of Contents</summary>

- [About](#about)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Roadmap](#roadmap)
- [Support](#support)
- [Project assistance](#project-assistance)
- [Contributing](#contributing)
- [Authors & contributors](#authors--contributors)
- [Security](#security)
- [License](#license)

</details>

---

## About

Zircon is a small IRC client made for UNIX and UNIX-like systems written in ANSI C.
The goal of Zircon is to be a very minimal, but fully featured IRC client that
can be compiled on many major UNIX and UNIX-like Operating Systems (Linux, macOS, *BSD).

<!-- <details> -->
<!-- <summary>Screenshots</summary> -->
<!-- <br> -->

<!-- |                                 Screenshot 1                              |                                 Screenshot 2                              | -->
<!-- | :-----------------------------------------------------------------------: | :-----------------------------------------------------------------------: | -->
<!-- | <img src="docs/images/screenshot1.png" title="Screenshot 1" width="100%"> | <img src="docs/images/screenshot2.png" title="Screenshot 2" width="100%"> | -->

<!-- </details> -->

## Getting Started

### Prerequisites

- Own a computer with Linux/macOS/*BSD installed.
- Have `gmake`, `gcc` and `ld` installed.

### Installation

```bash
make
sudo make install
```

Compiled binary is also available in `bin/zircon`

## Usage

```bash
zircon <server>:<port> [-s]
```

All arguments are optional, as you can connect to a network when already running Zircon.

## Roadmap

See the [open issues](https://github.com/schkwve/zircon/issues) for a list of proposed features (and known issues).

- [Top Feature Requests](https://github.com/schkwve/zircon/issues?q=label%3Aenhancement+is%3Aopen+sort%3Areactions-%2B1-desc) (Add your votes using the 👍 reaction)
- [Top Bugs](https://github.com/schkwve/zircon/issues?q=is%3Aissue+is%3Aopen+label%3Abug+sort%3Areactions-%2B1-desc) (Add your votes using the 👍 reaction)
- [Newest Bugs](https://github.com/schkwve/zircon/issues?q=is%3Aopen+is%3Aissue+label%3Abug)

## Support

Reach out to the maintainer at one of the following places:

- [GitHub issues](https://github.com/schkwve/zircon/issues/new?assignees=&labels=question&template=04_SUPPORT_QUESTION.md&title=support%3A+)
- Mail at [schkwve@gmail.com](mailto:schkwve@gmail.com)
- Discord at `ethernet.rj45`

## Contributing

First off, thanks for taking the time to contribute! Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make will benefit everybody else and are **greatly appreciated**.

For a place to start, take a look at [GitHub issues](https://github.com/schkwve/zircon/issues?q=is%3Aopen+is%3Aissue+label%3Abug) to fix, or our [TODO list](TODO).

Please read [our contribution guidelines](docs/CONTRIBUTING.md), and thank you for being involved!

## Authors & contributors

The original setup of this repository is by [Jozef Nagy](https://github.com/schkwve).

For a full list of all authors and contributors, see [the contributors page](https://github.com/schkwve/zircon/contributors).

## Security

Zircon follows good practices of security, but 100% security cannot be assured.
Zircon is provided **"as is"** without any **warranty**. Use at your own risk.

_For more information and to report security issues, please refer to our [security documentation](docs/SECURITY.md)._

## License

This project is licensed under the **BSD license**.

See [LICENSE](LICENSE) for more information.
